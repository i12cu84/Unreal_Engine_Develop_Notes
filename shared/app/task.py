import gym
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.tensorboard import SummaryWriter
import numpy as np
import random
from collections import deque
from tqdm import tqdm

class DQN(nn.Module):
    def __init__(self, state_dim, action_dim):
        super(DQN, self).__init__()
        self.fc1 = nn.Linear(state_dim, 64)
        self.fc2 = nn.Linear(64, 64)
        self.fc3 = nn.Linear(64, action_dim)

    def forward(self, x):
        x = torch.relu(self.fc1(x))
        x = torch.relu(self.fc2(x))
        x = self.fc3(x)
        return x

class Agent():
    def __init__(self, state_dim, action_dim, memory_size=10000, batch_size=64, gamma=0.99, lr=1e-3):
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.state_dim = state_dim
        self.action_dim = action_dim
        self.memory = deque(maxlen=memory_size) # deque是一个双端队列，可以在队首或队尾插入或删除元素。在DQN算法中，我们使用deque实现经验池来存储之前的经验，因为它可以在队尾插入新的经验，并在队首删除最老的经验，从而保持经验池的大小不变。
        self.batch_size = batch_size
        self.gamma = gamma
        self.lr = lr
        self.policy_net = DQN(state_dim, action_dim).to(self.device)
        self.target_net = DQN(state_dim, action_dim).to(self.device)
        self.optimizer = optim.Adam(self.policy_net.parameters(), lr=self.lr)
        self.loss_fn = nn.MSELoss()
        self.steps = 0
        self.writer = SummaryWriter()

    def select_action(self, state, eps):
        if np.random.rand() < eps:
            return random.randint(0, self.action_dim - 1)
        else:
            if len(state) != 4:
                # 如果状态长度不为4，则打印一条消息并返回一个随机动作
                #print("Invalid state length. Expected length 4, got:", len(state))
                return random.randint(0, self.action_dim - 1)

            state = torch.FloatTensor(state).to(self.device)
            with torch.no_grad():
                action = self.policy_net(state).argmax().item()

            return action


    def store_transition(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))

    def train(self):
        if len(self.memory) < self.batch_size:
            return

        transitions = random.sample(self.memory, self.batch_size)

        # 添加检查并排除不符合预期结构的转换
        valid_transitions = []
        for transition in transitions:
            if len(transition) == 5 and isinstance(transition[0], np.ndarray):
                valid_transitions.append(transition)
            #else:
                #print("Skipped invalid transition:", transition)

        # 如果没有有效的转换，直接返回
        if not valid_transitions:
            return

        batch = list(zip(*valid_transitions))

        print(torch.FloatTensor(batch[0]).to(self.device))

        state_batch = torch.FloatTensor(batch[0]).to(self.device)
        action_batch = torch.LongTensor(batch[1]).to(self.device)
        reward_batch = torch.FloatTensor(batch[2]).to(self.device)
        next_state_batch = torch.FloatTensor(batch[3]).to(self.device)
        done_batch = torch.FloatTensor(batch[4]).to(self.device)

        q_values = self.policy_net(state_batch).gather(1, action_batch.unsqueeze(1)).squeeze(1)
        next_q_values = self.target_net(next_state_batch).max(1)[0]
        expected_q_values = reward_batch + self.gamma * next_q_values * (1 - done_batch)

        loss = self.loss_fn(q_values, expected_q_values.detach())

        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

        self.steps += 1
        self.writer.add_scalar("Loss", loss.item(), self.steps)

    def update_target(self):
        self.target_net.load_state_dict(self.policy_net.state_dict())

def train_dqn(env, agent, eps_start=1, eps_end=0.1, eps_decay=0.995, max_episodes=1000, max_steps=1000):
    eps = eps_start
    for episode in tqdm(range(max_episodes)):
        state = env.reset()
        for step in range(max_steps):
            action = agent.select_action(state, eps)

            next_state, reward, done, info, _ = env.step(action)
            
            agent.store_transition(state, action, reward, next_state, done)
            state = next_state
            
            agent.train()
            if episode % 20 == 0:
              env.render()
            if done:
                break
        agent.update_target()
        eps = max(eps * eps_decay, eps_end)

if __name__ == "__main__":
    env = gym.make("CartPole-v1")
    state_dim = env.observation_space.shape[0]
    action_dim = env.action_space.n
    agent = Agent(state_dim, action_dim)
    train_dqn(env, agent)