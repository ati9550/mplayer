#include "coverlabel.h"

CoverLabel::CoverLabel() {
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->reset();
}
CoverLabel::~CoverLabel() {}

void CoverLabel::resizeEvent(QResizeEvent *event){
    this->image_data = image_original.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(image_data);
    this->resize(event->size());
}
void CoverLabel::set_new_cover(QPixmap new_cover_image) {
    this->image_original = new_cover_image;
    this->image_data = image_original.scaled(QWidget::size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(this->image_data);
}
void CoverLabel::reset() {
    this->set_new_cover(QPixmap("cover.jpg"));
}
