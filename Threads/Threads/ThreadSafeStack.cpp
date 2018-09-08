#include <stack>
#include <mutex>
#include <memory>

template <typename T>
class ThreadSafeStack {
private:
	std::stack<T> st;
	mutable std::mutex mut;

public:
	ThreadSafeStack() {}

	ThreadSafeStack(const ThreadSafeStack& other) {
		std::lock_guard<std::mutex> lk(other.mut);
		st = other.st;
	}

	ThreadSafeStack operator = (const ThreadSafeStack&) = delete;

	void push(T value) {
		std::lock_guard<std::mutex> lk(mut);
		st.push(value);
	}

	std::shared_ptr<T> pop() {
		std::lock_guard<std::mutex> lk(mut);
		auto const ptr = std::shared_ptr<T>(std::move(st.top()));
		st.pop();
		return ptr;
	}

	void pop(T& value) {
		std::lock_guard<std::mutex> lk(mut);
		value = std::move(st.top());
		st.pop();
	}

	bool empty() const {
		std::lock_guard<std::mutex> lk(mut);
		return st.empty();
	}
};