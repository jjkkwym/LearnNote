# 类

private：私有成员只能在其所属类的内部访问，对外部代码是不可见的。它们对于派生类和其他类的对象都是不可访问的。
protected：受保护成员可以在其所属类的内部和派生类中访问，但对于其他类的对象来说是不可见的。

## 私有函数和公有函数 

在 C++ 中，函数的私有（private）和公有（public）是访问控制修饰符，用于限定类中成员函数的访问权限。下面是它们的区别：

私有函数（private function）：

私有函数只能在当前类的成员函数中被调用，外部代码无法直接访问私有函数。
私有函数对于类的使用者来说是不可见的，只能在类的内部使用。
私有函数通常用于实现类的内部逻辑、辅助函数等，对于外部代码来说是隐藏的。
可以通过公有函数或友元函数来间接调用私有函数。
公有函数（public function）：

公有函数可以被类的使用者直接调用，也可以在类的内部使用。
公有函数对于类的使用者来说是可见的，可以通过对象或类名加上成员访问操作符 . 或 -> 来调用公有函数。
公有函数定义了类的接口，是类和外部代码的交互点。
公有函数可以被继承和派生类使用。
下面是一个简单示例，展示了私有函数和公有函数的使用：

cpp
class MyClass {
private:
    void privateFunction() {
        cout << "This is a private function." << endl;
    }
    
public:
    void publicFunction() {
        cout << "This is a public function." << endl;
        privateFunction();  // 在公有函数中调用私有函数
    }
};

int main() {
    MyClass obj;
    
    obj.publicFunction();  // 可以直接调用公有函数
    // obj.privateFunction();  // 错误，无法直接调用私有函数
    
    return 0;
}
在上面的示例中，MyClass 类中定义了一个私有函数 privateFunction 和一个公有函数 publicFunction。公有函数可以直接被外部代码调用，而私有函数只能在类的内部使用。在公有函数 publicFunction 中，我们调用了私有函数 privateFunction。

总结起来，私有函数和公有函数的区别在于其访问权限和可见性。私有函数对于外部代码是不可见的，只能在类内部使用；而公有函数可以被外部代码直接调用，是类与外界交互的接口。