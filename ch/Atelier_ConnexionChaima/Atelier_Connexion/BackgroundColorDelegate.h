#ifndef BACKGROUNDCOLORDELEGATE_H
#define BACKGROUNDCOLORDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QPalette>

class BackgroundColorDelegate : public QStyledItemDelegate {
public:
    BackgroundColorDelegate(const QPalette &palette, QObject *parent = nullptr)
        : QStyledItemDelegate(parent), m_palette(palette) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        // Check for the 9th column


        if (index.column() == 9) {
                    painter->fillRect(option.rect, m_palette.color(QPalette::Background));

                    // Set the font to bold
                    QFont boldFont = painter->font();
                    boldFont.setBold(true);
                    painter->setFont(boldFont);

                    // Draw the 'Delete' text centered in the rectangle
                    painter->drawText(option.rect, Qt::AlignCenter, "Update");

                }
        else if (index.column() == 10) {
            painter->fillRect(option.rect, m_palette.color(QPalette::Background));

            // Set the font to bold
            QFont boldFont = painter->font();
            boldFont.setBold(true);
            painter->setFont(boldFont);

            // Draw the 'Delete' text centered in the rectangle
            painter->drawText(option.rect, Qt::AlignCenter, "Delete");

        }


        else {
            // Call the base class implementation for other columns
            QStyledItemDelegate::paint(painter, option, index);
        }
    }

private:
    QPalette m_palette; // Holds the palette for the background color
};

#endif // BACKGROUNDCOLORDELEGATE_H
