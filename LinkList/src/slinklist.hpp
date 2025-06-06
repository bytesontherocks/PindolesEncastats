// MIT License
//
// Copyright (c) [2025] [Guillem Coromina / BytesOnTheRocks]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once

#include <cinttypes>
#include <iostream>
#include <memory>

namespace ll {

    template <typename T>
    class Node {
      public:
        explicit Node(const T& val) : val(std::move(val)) {}
        std::shared_ptr<Node<T>> next{nullptr};
        T                        val;
    };

    template <typename T>
    class LinkedList {
      public:
        void push_back(std::shared_ptr<Node<T>> node_to_push) {
            if (!m_head) {
                std::cout << "list has been initialised - head has been set" << std::endl;
                m_head = std::move(node_to_push);
                m_tail = m_head;
                return;
            }

            // using tail
            auto& node_next{m_tail->next};
            node_next = std::move(node_to_push);
            m_tail    = node_next;
        };

        void push_front(std::shared_ptr<Node<T>> node_to_push) {
            if (!m_head) {
                std::cout << "list has been initialised - head has been set" << std::endl;
                m_head = std::move(node_to_push);
                m_tail = m_head;

                return;
            }

            node_to_push->next = m_head;
            m_head             = std::move(node_to_push);
        };

        std::shared_ptr<Node<T>> pop_front() {
            if (isEmpty()) {
                return nullptr;
            }

            auto& next = m_head->next;

            // head is the last node
            if (nullptr == next) {
                m_tail.reset();
                return std::move(m_head);
            }

            auto old_head = m_head;
            m_head        = std::move(next);

            return std::move(old_head);
        }

        bool isEmpty() const { return !m_head; };

        void printElements() {
            {
                auto next{m_head};
                while (nullptr != next) {
                    std::cout << "node with val: " << next->val << std::endl;
                    next = next->next;
                };
            }

            std::cout << "head ref counts: " << m_head.use_count() << std::endl;
            std::cout << "tail ref counts: " << m_tail.use_count() << std::endl;
        }

      private:
        std::shared_ptr<Node<T>> m_head{nullptr};
        std::shared_ptr<Node<T>> m_tail{nullptr};
    };

}  // namespace ll