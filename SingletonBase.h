#pragma once
#include <mutex>
#include<cassert>
template<typename T>
class SingletonBase{
public:
    // 删除拷贝构造函数和赋值操作符，确保单例
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;
    // 提供一个静态方法用于获取单例对象的引用
    static T& instance() {
        std::call_once(initInstanceFlag, &SingletonBase::initSingleton);//可以保证只调用一次
        assert(singletonInstance != nullptr);
        return *singletonInstance;
    }
protected:
    // 默认构造函数为protected，确保外部不能直接实例化
    SingletonBase() {}

    // 虚析构函数以支持派生类
    virtual ~SingletonBase() {}

private:
    // 静态方法用于初始化单例对象
    static void initSingleton() {
        singletonInstance = new T();
    }

    // 指向单例对象的静态指针
    inline static T* singletonInstance = nullptr;

    // 用于确保线程安全的一次性初始化标志
    inline static std::once_flag initInstanceFlag;
};
