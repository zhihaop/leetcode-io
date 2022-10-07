#ifndef LEETCODE_FORMATTER_LIST_H
#define LEETCODE_FORMATTER_LIST_H

#include <deque>

/**
 * Leetcode ListNode definition.
 */
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    explicit ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class List {
    std::deque<ListNode> allocator;
    ListNode *m_head{};
public:
    List() = default;

    List(const List &l) = delete;

    List(List &&l) noexcept: allocator(std::move(l.allocator)), m_head(l.m_head) {
        l.m_head = nullptr;
    }

    [[nodiscard]] ListNode *head() { return m_head; }

    [[nodiscard]] const ListNode *head() const { return m_head; }

    void emplace_front(int value) {
        if (!m_head) {
            m_head = &allocator.emplace_back();
            m_head->val = value;
            return;
        }

        auto h = m_head;
        m_head = &allocator.emplace_back();
        m_head->next = h;
        m_head->val = value;
    }
};

#endif //LEETCODE_FORMATTER_LIST_H
