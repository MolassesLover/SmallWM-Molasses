/** @file */
#ifndef __SMALLWM_SCREEN_MODEL__
#define __SMALLWM_SCREEN_MODEL__

#include "../common.h"

#include <ios>
#include <map>
#include <stack>
#include <vector>

// Note - I would have *preferred* to call these things Screen* rather than Crtc*,
// but XLib defines a Screen type already. I might introduce a SmallWM namespace
// later to clear this up, but Crt will work for now.

/**
 * Crts represent a graph of objects. They are used as keys in a map, so
 * they don't actually contain any data.
 *
 * Note that these are ephemeral - any time there is a change of screens, all
 * windows should update their current screen. Thankfully, however, screens
 * don't change themselves all the time.
 */
struct Crt {
    Crt *left, *right, *top, *bottom;

    /**
     * An identifier assigned to the screen, used only for dumped output
     *
     * The only rule is that this must be least on the root screen, and
     * greater on values away from the root - this ensures a readable ordering
     * when dumping.
     */
    int id;

    Crt(int _id) :
        left(NULL), right(NULL), top(NULL), bottom(NULL), id(_id),
        m_deleting(false) {
    }

    ~Crt() {
        m_deleting = true;

        // Note that we have to break all links when deleting the screen, since
        // we don't want to get trapped in a cycle
        if (left && !left->m_deleting) {
            left->right = NULL;
            delete left;
        }

        if (right && !right->m_deleting) {
            right->left = NULL;
            delete right;
        }

        if (top && !top->m_deleting) {
            top->bottom = NULL;
            delete top;
        }

        if (bottom && !bottom->m_deleting) {
            bottom->top = NULL;
            delete bottom;
        }
    }

private:
    /// This is used to avoid cycles when deleting a Crt
    bool m_deleting;
};

/**
 * This captures the graph of screens, mapping each screen to its bonding box,
 * and allows for searching among the screens.
 */
class CrtManager {
public:
CrtManager() : m_root(NULL) {
}

~CrtManager() {
    delete m_root;
}

Crt * root() const {
    return m_root;
}

Crt * screen_of_coord(Dimension, Dimension) const;
const Box &box_of_screen(Crt *) const;
Crt * screen_of_box(const Box &box);

void rebuild_graph(std::vector<Box>&);

void dump(std::ostream&);

private:
int build_node(Crt *, std::map<Dimension2D, Box>&, int);
void build_id_map(Crt *, std::map<int, Crt *>&);

/// The root screen is located at (0, 0). Guaranteed not to be NULL
Crt *m_root;

/// The bounding box of each screen
std::map<Crt *, Box> m_boxes;
};

#endif // ifndef __SMALLWM_SCREEN_MODEL__
