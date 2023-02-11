#include "guimoves.h"
#include <string>
#include <iostream>
#include <stack>

static char piecename_to_str(PieceName p, Color c) {
  char piece = ' ';
  if (c == Color::White) {
    switch(p) {
      case PieceName::King: piece = 'K'; break;
      case PieceName::Queen: piece = 'Q'; break;
      case PieceName::Bishop: piece = 'B'; break;
      case PieceName::Knight: piece = 'N'; break;
      case PieceName::Rook: piece = 'R'; break;
      case PieceName::Pawn: piece = 'P'; break;
    }
  } else if (c == Color::Black) {
    switch(p) {
      case PieceName::King: piece = 'k'; break;
      case PieceName::Queen: piece = 'q'; break;
      case PieceName::Bishop: piece = 'b'; break;
      case PieceName::Knight: piece = 'n'; break;
      case PieceName::Rook: piece = 'r'; break;
      case PieceName::Pawn: piece = 'p'; break;
    }
  }
  return piece;
}

static std::string move_to_str(std::shared_ptr<const Move> m) {
  std::string movestring = "";
  char name = piecename_to_str(m->piecename, Color::White);
  if (name != 'P') {
    movestring += name;
  }
  movestring += m->pref;
  if (m->mt == MoveType::Capture) {
      movestring += "x";
  }
  char col = 'a' - 1 + m->to->get_col();
  char row = '0' + m->to->get_row();
  movestring += col;
  movestring += row;
  movestring += " ";
  return movestring;
}

GUIMoves::GUIMoves(std::shared_ptr<Board> b)
  : GUIElem(b)
{
  if(TTF_Init() != 0) {
    exit(1);
  }
  this->reg = TTF_OpenFontDPI("assets/fonts/OpenSans-Regular.ttf", 7, 250, 250);
  this->bold = TTF_OpenFontDPI("assets/fonts/OpenSans-Bold.ttf", 7, 250, 250);
  root = std::make_shared<Node>();
  root->parent = nullptr;
}

void GUIMoves::load_assets(SDL_Renderer *r) {
  return;
}

void GUIMoves::handle(SDL_Renderer *r, SDL_Event *e) {
  if (r == nullptr || e == nullptr) {
    return;
  }
  switch(e->type) {
    case SDL_KEYDOWN:
      switch(e->key.keysym.sym) {
	case SDLK_LEFT:
	  b->move_back();
	  break;
	case SDLK_RIGHT:
	  b->move_forward(0); // change this to ask for which move to move forward to (among different variations)
	  break;
	default:
	  break;
      }
  }
  this->update(r);
  this->notify_observers(r);
  return;
}

void GUIMoves::find_drawing_rectangles(SDL_Renderer *r) {
  std::stack<std::shared_ptr<Node>> nodes;
  std::stack<int> xs;
  nodes.push(root);
  int x = 0;
  int y = 0;
  int w = 0;
  int h = 0;
  xs.push(x);
  while(!nodes.empty()) {
    printf("hi");
    auto temp = nodes.top();
    nodes.pop();
    x = xs.top();
    xs.pop();
    if (SDL_QueryTexture(temp->t, NULL, NULL, &w, &h) == 0) {
      SDL_Rect rect = { x, y, w, h };
      temp->position = rect;
      SDL_RenderCopy(r, temp->t, NULL, &rect);
      if (x + w > viewport->w) {
	x = 0;
	y += h;
      } else {
	x += w;
      }
    }

    // TODO: set temp rect
    if (temp->children.size() == 0) {
      y += h;
      continue;
    }
    if (temp->children.size() > 1) {
      y += h;
      xs.push(0);
    } else {
      xs.push(x);
    }
    nodes.push(temp->children[0]);
    for (int i = temp->children.size() - 1; i >= 1; i--) {
      xs.push(x);
      nodes.push(temp->children[i]);
    }
  }
  SDL_RenderPresent(r);
  return;
}

void GUIMoves::update(SDL_Renderer *r) {
  SDL_RenderSetViewport(r, viewport);
  auto [begin, end] = b->get_moves_const_iter();
  int move_num = 0;
  while(root->parent != nullptr) {
    root = root->parent;
  }
  if (root == nullptr) {
    root = std::make_shared<Node>();
    root->parent = nullptr;
  }
  for (auto temp = begin; temp != end; ++temp) {
    if (temp.get_tree_traversal() == TreeTraversal::NewNode) {
      int i = 0;
      for (; i < root->children.size(); i++) {
	if ((*temp) == root->children[i]->m) {
	  break;
	}
      }
      if (i < root->children.size()) {
	root->next_node_idx = root->children.size() > 1;
	root = root->children[i];
	if (root->m->color == Color::White) {
	  move_num++;
	}
	continue;
      }
      bool is_main_variation = root->children.size() == 0;
      root->next_node_idx = root->children.size() > 0;
      auto node = std::make_shared<Node>();
      node->m = (*temp);
      node->parent = root;
      root->children.push_back(node);
      root = node;
      std::string move = "";
      if (node->m->color == Color::White) {
	move_num++;
	move = move + std::to_string(move_num) + ". ";
      }
      move += move_to_str(node->m);
      auto text_surface = TTF_RenderText_Blended_Wrapped(is_main_variation ? bold : reg, move.c_str() , { 0, 0, 0, 255 }, 300);
      auto text_texture = SDL_CreateTextureFromSurface(r, text_surface);
      root->t = text_texture;
    } else if (temp.get_tree_traversal() == TreeTraversal::Backtrack) {
      root = root->parent;
      if ((*temp)->color == Color::Black) {
	move_num--;
      }
    }
  }

  // now present the above info in a nice way on the screen.
  while(root->parent != nullptr) {
    if (root->t == nullptr) {
      std::cout << "Texture is Null" << std::endl;
    }
    root = root->parent;
  }


  std::cout << "Next Node Idx:" << root->next_node_idx << std::endl;
  
  int total_height = 0;
  int total_width = 0;
  bool is_backtrack = false;
  SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
  SDL_Rect thisrect = {0, 0, viewport->w, viewport->h};
  SDL_RenderFillRect(r, &thisrect);
  this->find_drawing_rectangles(r);

  while(root->parent != nullptr) {
    root = root->parent;
  }
  SDL_RenderPresent(r);
  return;
}

GUIMoves::~GUIMoves(void) {
  TTF_CloseFont(reg);
  TTF_CloseFont(bold);
  TTF_Quit();
}
