#ifndef LEETCODE_LIST_H
#define LEETCODE_LIST_H

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

using Node = ListNode;

class List {
    ListNode *m_head{};
public:
    List() = default;

    List(const List &l) = delete;

    List(List &&l) noexcept: m_head(l.m_head) {
        l.m_head = nullptr;
    }

    ~List() {
        if (!m_head) return;
        auto node = m_head;
        do {
            auto next = node->next;
            delete node;
            node = next;
        } while (node != m_head && node);
    }

    [[nodiscard]] ListNode *head() { return m_head; }

    [[nodiscard]] const ListNode *head() const { return m_head; }

    [[nodiscard]] ListNode * tail() {
        auto node = m_head;
        while (node) {
            if (!node->next || node->next == m_head) return node;
            node = node->next;
        }
        return node;
    }

    [[nodiscard]] const ListNode * tail() const {
        auto node = m_head;
        while (node) {
            if (!node->next || node->next == m_head) return node;
            node = node->next;
        }
        return node;
    }

    void cycling() {
        auto t = tail();
        if (t)  t->next = head();
    }

    void emplace_front(int value) {
        if (!m_head) {
            m_head = new ListNode();
            m_head->val = value;
            return;
        }

        auto h = m_head;
        m_head = new ListNode();
        m_head->next = h;
        m_head->val = value;
    }
};

#endif //LEETCODE_LIST_H
