#ifndef MOVETREE_H_
#define MOVETREE_H_

#include <memory>
#include <vector>
#include <variant>
#include "move.h"

enum TreeTraversal { NewNode, Backtrack };

using MoveCIter = std::vector<Move>::const_iterator;
using MoveCIterPair = std::pair<MoveCIter, MoveCIter>;
// using MoveCIter = std::vector<std::pair<std::vector<Move>::const_iterator, std::>>>;

class MoveTree {
  struct Node {
    std::shared_ptr<Move> m;
    std::shared_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children;
  };
  std::shared_ptr<Node> root;
  std::shared_ptr<Node> cur;
  size_t len;
  public:
  MoveTree(void);
  size_t size(void);
  // should be unique_ptr, but will need to change a lot of the other code
  // to make unique_ptr work.
  void add_move(std::shared_ptr<Move> m);
  std::shared_ptr<Move> get_current_move(void);
  std::shared_ptr<Move> get_prev_move(void); // doesn't change cur
  bool prev_move(void);
  bool next_move(int variation=0);
  std::vector<MoveCIterPair> get_move_const_iterators(void);
  ~MoveTree(void);

  class const_iterator {
    std::shared_ptr<Node> root;
    TreeTraversal t;
    int cur_idx = 0;
    public:
    using difference_type = std::shared_ptr<const Move>;
    using value_type = std::shared_ptr<const Move>;
    using pointer = std::shared_ptr<const Node>;
    using reference = std::shared_ptr<const Move>&;
    using iterator_category = std::forward_iterator_tag;

    const_iterator(std::shared_ptr<Node> n);
    const_iterator& operator++(void);
    const_iterator operator++(int n);
    bool operator==(const_iterator other);
    bool operator!=(const_iterator other);
    std::shared_ptr<const Move> operator*(void);
    TreeTraversal get_tree_traversal(void);
  };
  const_iterator cbegin(void);
  const_iterator cend(void);
};

#endif
