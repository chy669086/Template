
template<class T, class _cmp = std::less<>>
class Heap {
public:
    void insert(const T& x) {
        q1.push(x);
    }

    void erase(const T& x) {
        q2.push(x);

        while (!q2.empty() && q1.top() == q2.top()) {
            q1.pop();
            q2.pop();
        }
    }

    T top() {
        return q1.top();
    }

    std::size_t size() {
        return q1.size() - q2.size();
    }
private:
    std::priority_queue<T, std::vector<T>, _cmp> q1, q2;
};