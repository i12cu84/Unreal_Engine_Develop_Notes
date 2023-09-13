多线程

|compare|Thread|FRunnable|
|-|-|-|
|应用场景|各线程相互独立|各线程协作完成任务、共享资源|
|分析|复杂/局限高|简易,不需要继承类,避免了单继承的局限|

使用方法
(1) 实现Runnable接口
(2) 重写run()方法
(3) 创建runnable实例
(4) 创建Thread实例
(5) 将Runnable实例放入Thread实例中
(6) 通过线程实例控制线程的行为(运行，停止)，在运行时会调用Runnable接口中的run方法。

注意:Java中真正能创建新线程的只有Thread类对象
通过实现Runnable的方式，最终还是通过Thread类对象来创建线程
Runnable方式也分为标准方式和匿名方式

(1)标准方式
```
public class MainActivity extends AppCompatActivity {
    Button btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        btn = findViewById(R.id.btn);
        //2.创建MyRunnable实例
        MyRunnable runnable=new MyRunnable();
        //3.创建Thread对象
        //4.将MyRunnable放入Thread实例中
        Thread thread=new Thread(runnable);
        //5.通过线程对象操作线程(运行、停止)
        thread.start();
    }
    //1.实现runnable接口并重写run方法
    class MyRunnable implements Runnable{
        @Override
        public void run() {
        }
    }
}
```
(2)匿名方式
```
public class MainActivity extends AppCompatActivity {
    Button btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //1.匿名实现Runnable接口并重写run方法
        Runnable runnable = new Runnable() {
            @Override
            public void run() {

            }
        };
        //2.创建线程对象
        //3.将runnable实例放入线程对象中
        Thread thread=new Thread(runnable);
        //4.由线程实例控制线程的行为(运行，停止)
        thread.start();
    }
}
```

参考资料:
https://www.jianshu.com/p/0c9a74ef87ef
https://blog.csdn.net/zhaojianting/article/details/97664370