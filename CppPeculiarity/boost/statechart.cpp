#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <iostream>

namespace sc = boost::statechart;

struct Idle;
struct Active;

struct SimpleStateMachine : sc::state_machine<SimpleStateMachine, Idle> {};

struct Idle : sc::simple_state<Idle, SimpleStateMachine> {
    Idle() {
        std::cout << "Entering Idle state." << std::endl;
    }
};

struct Active : sc::simple_state<Active, SimpleStateMachine> {
    Active() {
        std::cout << "Entering Active state." << std::endl;
    }
};

int main() {
    SimpleStateMachine machine;
    machine.initiate();
    machine.process_event(sc::state_machine<SimpleStateMachine>::start());
}
