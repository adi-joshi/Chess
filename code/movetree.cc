#include "movetree.h"
#include <iostream>

MoveTree::MoveTree(void) {
  root = std::make_shared<Node>();
  root->parent = nullptr;
  root->m = nullptr;
  cur = root;
  this->len = 0;
}

size_t MoveTree::size(void) {
  return this->len;
}

void MoveTree::add_move(std::shared_ptr<Move> m) {
  for (int i = 0; i < cur->children.size(); i++) {
    if (cur->m == m) {
      cur = cur->children[i];
      return;
    }
  }
  auto node = std::make_shared<Node>();
  node->parent = cur;
  node->m = std::move(m);
  cur->children.push_back(node);
  cur = cur->children[cur->children.size() - 1]; // m
  len++;
  return;
}

std::shared_ptr<Move> MoveTree::get_current_move(void) {
  return cur->m;
}

std::shared_ptr<Move> MoveTree::get_prev_move(void) {
  if (cur->parent == nullptr) {
    return nullptr;
  } else {
    return cur->parent->m;
  }
}

bool MoveTree::prev_move(void) {
  if (cur->parent == nullptr) {
    return false;
  }
  cur = cur->parent;
  return true;
}

bool MoveTree::next_move(int variation) {
  if (cur->children.size() <= variation) {
    return false;
  }
  cur = cur->children[variation];
  return true;
}

MoveTree::~MoveTree(void) {}

MoveTree::const_iterator MoveTree::cbegin(void) {
  return MoveTree::const_iterator{root};
}

MoveTree::const_iterator MoveTree::cend(void) {
  return MoveTree::const_iterator{nullptr};
}

//-----------const_iterator---------------

MoveTree::const_iterator::const_iterator(std::shared_ptr<Node> n)
  : root{n}
{
  t = TreeTraversal::NewNode;
}

// prefix ++
MoveTree::const_iterator& MoveTree::const_iterator::operator++(void) {
  if (root->children.size() <= cur_idx && root->parent == nullptr) {
    // std::cout << "End" << std::endl;
    t = TreeTraversal::NewNode;
    root = nullptr;
    return *this;
  } else if (root->parent != nullptr && root->children.size() <= cur_idx && root->parent->m == nullptr) {
    // std::cout << "End" << std::endl;
    t = TreeTraversal::NewNode;
    root = nullptr;
    return *this;
  } else if (root->children.size() <= cur_idx) {
    t = TreeTraversal::Backtrack;
    auto temp = root;
    root = root->parent;
    int i = 0;
    for (; i < root->children.size(); i++) {
      if (temp->m == root->children[i]->m) {
	break;
      }
    }
    cur_idx = i + 1;
    // std::cout << "Backtrack: " << root->m->to->get_col() << " " << root->m->to->get_row() << " with cur_idx = " << cur_idx << std::endl;
    return *this;
  } else {
    t = TreeTraversal::NewNode;
    root = root->children[cur_idx];
    cur_idx = 0;
    // std::cout << "New Node: " << root->m->to->get_col() << " " << root->m->to->get_row() << std::endl;
    return *this;
  }
}

// postfix ++. int argument is just to differentiate between prefix ++
MoveTree::const_iterator MoveTree::const_iterator::operator++(int n) {
  return this->operator++();
}

bool MoveTree::const_iterator::operator==(MoveTree::const_iterator other) {
  return root == other.root;
}

bool MoveTree::const_iterator::operator!=(MoveTree::const_iterator other) {
  return !(root == other.root);
}

std::shared_ptr<const Move> MoveTree::const_iterator::operator*(void) {
  return root->m;
}
TreeTraversal MoveTree::const_iterator::get_tree_traversal(void) {
  return t;
}
