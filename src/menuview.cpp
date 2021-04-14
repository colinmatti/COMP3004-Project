#include "menuView.h"

/**
 * @brief Given a MenuView, construct a QStringListModel of menu options.
 * @param MenuView view: the current menu view from which we collect menu options.
 * @return Populated menu list.
 */
QStringList MenuView::constructMenu() {
    QStringList menu = QStringList();
    for (View* option : *children) { menu.append(option->getName()); }
    return menu;
}
