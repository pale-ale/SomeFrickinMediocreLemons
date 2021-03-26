#pragma once

template<typename ...Is>
class IEventCallback{
    public:
	virtual void operator() (Is... is) = 0;
};

template<typename T, typename ...Args>
class EventCallback : public IEventCallback<Args...>
{
public:
	EventCallback(T* instance, void (T::*function)(Args...))
		: instance(instance), function(function) {}    
	virtual void operator()(Args... args) override { (instance->*function)(args...); }    

private:
	void (T::*function)(Args... args);
	T* instance;
};