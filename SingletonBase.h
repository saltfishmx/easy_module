#pragma once
#include <mutex>
#include<cassert>
template<typename T>
class SingletonBase{
public:
	// ɾ���������캯���͸�ֵ��������ȷ������
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;
    // �ṩһ����̬�������ڻ�ȡ�������������
    static T& instance() {
        std::call_once(initInstanceFlag, &SingletonBase::initSingleton);//���Ա�ֻ֤����һ��
        assert(singletonInstance != nullptr);
        return *singletonInstance;
    }
protected:
    // Ĭ�Ϲ��캯��Ϊprotected��ȷ���ⲿ����ֱ��ʵ����
    SingletonBase() {}

    // ������������֧��������
    virtual ~SingletonBase() {}

private:
    // ��̬�������ڳ�ʼ����������
    static void initSingleton() {
        singletonInstance = new T();
    }

    // ָ��������ľ�ָ̬��
    inline static T* singletonInstance = nullptr;

    // ����ȷ���̰߳�ȫ��һ���Գ�ʼ����־
    inline static std::once_flag initInstanceFlag;
};