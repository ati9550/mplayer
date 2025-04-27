#ifndef MEDIASLIDER_H
#define MEDIASLIDER_H

#include <QtWidgets/QSlider>
#include <QMouseEvent>

class MediaSlider: public QSlider {
protected:
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif // MEDIASLIDER_H
