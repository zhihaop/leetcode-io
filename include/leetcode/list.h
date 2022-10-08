#ifndef LEETCODE_LIST_H
#define LEETCODE_LIST_H

/**
 * Leetcode ListNode definition.
 */
struct ListNode {
    int val{};
    ListNode *next{};

    ListNode() = default;

    [[maybe_unused]] explicit ListNode(int x) : val(x), next(nullptr) {}

    [[maybe_unused]] ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using Node = ListNode;

class ForwardList {
    ListNode *m_head{};
public:
    ForwardList() = default;

    ForwardList(const ForwardList &l) = delete;

    ForwardList(ForwardList &&l) noexcept: m_head(l.m_head) {
        l.m_head = nullptr;
    }

    ~ForwardList() {
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

    [[nodiscard]] ListNode *tail() {
        auto node = m_head;
        while (node) {
            if (!node->next || node->next == m_head) return node;
            node = node->next;
        }
        return node;
    }

    [[nodiscard]] const ListNode *tail() const {
        auto node = m_head;
        while (node) {
            if (!node->next || node->next == m_head) return node;
            node = node->next;
        }
        return node;
    }

    /**
     * Make the forward list become a circular forward list
     */
    [[maybe_unused]] void cycling() {
        auto t = tail();
        if (t) t->next = head();
    }

    /**
     * Undo the ForwardList::cycling() operation.
     */
    [[maybe_unused]] void undo_cycling() {
        auto t = tail();
        if (t) t->next = nullptr;
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
