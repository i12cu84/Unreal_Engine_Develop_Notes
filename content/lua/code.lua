print("string")     --打印
nano 文件名.lua     --创建

num=100 --全局变量
local num=100 --局部变量
print(num)

function max(a,b)
    if a>b then
        return a
    else 
        return b
    end
end
print(max(2,3))

for var=1,100 do
    print(var)
end

--表 (类似键值对)
config={} --建立空表
config={hello="hello lua",world="world"}
config.words="hello"
config.num=100
config["name"]="zs"

print(config["words"])
print(config.name)
print(config.hello)

for key,car in pairs(config) do
    print(key,var)
end


arr={1,2,3,4,"string"}
for key,var in pairs(arr) do
    print(key,var)
end
--数组索引从1开始
arr={}
for var=1,100 do
    table.insert(arr,1,var) --注意从第一开始
end

for key,var in pairs(arr) do
    print(key,var)
end

print(table.maxn(arr)) --最大索引

--复制表面向对象
people={}
people.sayhi=function()
--或者 
function people.sayhi(self)
    print("hi"..self.name) --两点代表字符串连接
end

--克隆
function clone(table)
    local ins={}
    for key,var in pairs(tab) do
        ins[key]=var
    end
    return ins
end
--或者
local p=clone(people)
p.sayhi()

--方法2
people.new =function(name)
    local self=clone(people)
    selp.name=name
    return self
end

local p=people.new("zs")
p.sayhi(p)
--等价于
p:sayhi()

--类的继承
function copy(dist,tab)
    for key,var in pairs(tab) do
        dist[key]=var
    end
end
man={}
man.new=function(name)
    local self=people.new(name)
    copy(self,man)
    --用于拷贝继承
    return self
end

man.sayhello=function()
    print("man say hello")
end

man.sayhi=function(self)
    print("man sayhi"..self.name)
end

local m=man.new("ls")
m:sayhello()

--函数闭包->面向对象
funcation people(name)
    local self={}
    local function init()
        self.name=name
    end
    self.sayhi=function()
        print("hello"..self.name)
    end

    init()
    return self
end
local p=people("zs")
p:sayhi()

--继承
function man(name)
    local self=people(name)
    local function init()

    end

    self.sayhello=function()
        print("hi"..self.name)
    end
    return self
end

local m=man("ls")
m:sayhello()
m:sayhi()
