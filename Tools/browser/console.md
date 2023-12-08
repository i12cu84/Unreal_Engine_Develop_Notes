基本命令
console.log()：用于输出信息到控制台。



console.log("这是一条信息");
console.error()：当发生错误时，输出错误信息到控制台。



console.error("出错了！");
console.dir()：用于展示对象的所有属性和方法。



var obj = { name: "张三", age: 25 };
console.dir(obj);
console.group()和console.groupEnd()：用于将相关的console命令组织在一起，形成一个分组。



console.group("个人信息");
console.log("姓名： " + name);
console.log("年龄： " + age);
console.groupEnd();
console.time()和console.timeEnd()：用于计时，可以计算代码块的执行时间。



console.time("计时开始");
// ... 你的代码 ...
console.timeEnd("计时结束");
高级功能
inspect(element)：选取页面上的一个元素，并在开发者工具中显示它的详细信息。



inspect(document.querySelector(".my-class"));
getEventListeners(element)：显示指定元素上注册的所有事件监听器。
monitorEvents(element, eventNames)：开始监控指定元素上的特定事件。
unmonitorEvents(element, eventNames)：停止监控指定元素上的特定事件。

注意事项
部分命令可能仅在支持javascript的控制台中有效。
某些命令可能需要特定浏览器或开发者工具的扩展支持。


当然，以下是一些其他使用浏览器console命令行的示例和用法：
1. **查看网络请求**：

   console.log(performance.getEntriesByType('navigation'));

2. **计算函数执行时间**：

   console.time('myFunction');
   myFunction();
   console.timeEnd('myFunction');

3. **监听DOM变化**：

   console.log('DOM变化', performance.now());

4. **使用表达式求值**：

   console.log((2 + 2));

5. **查看当前的JavaScript作用域**：

   console.dir(window.global);

6. **查看CSS样式**：

   console.log(getComputedStyle(document.documentElement));

7. **执行JavaScript文件**：

   console.log(eval("require('fs').readFileSync('path/to/file.js', 'utf8')"));

8. **使用RegExp**：

   console.log('myString'.match(/myPattern/g));

9. **查看本地存储**：

   console.log(localStorage.getItem('myKey'));

10. **使用数组方法**：

    console.log([1, 2, 3].map(function(item) { return item * 2 }));
 
11. **查看Promise**：

    console.log(new Promise((resolve, reject) => {
      setTimeout(() => resolve('Success'), 2000);
    }));
 
12. **查看错误**：

    try {
      // 某些可能会抛出错误的代码
    } catch (error) {
      console.error(error);
    }
 
这些只是一些示例，实际上，你可以在console中执行任何有效的JavaScript代码。它是一个强大的调试和开发工具，可以帮助你更好地理解你的代码和应用程序的行为。

参考资料
https://blog.csdn.net/csucsgoat/article/details/117847018
https://blog.csdn.net/csucsgoat/article/details/117811466