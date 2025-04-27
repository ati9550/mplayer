#ifndef COVERCLASS_H
#define COVERCLASS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class CoverLabel : public QLabel {
    Q_OBJECT
private:
    QPixmap image_data;
    QPixmap image_original;
public:
    CoverLabel();
    ~CoverLabel();
    void set_new_cover(QPixmap new_cover_image);
    void reset();
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // COVERCLASS_H
