#ifndef STATISTIQUEF_H
#define STATISTIQUEF_H

#include <QDialog>

namespace Ui {
class statistiquef;
}

class statistiquef : public QDialog
{
    Q_OBJECT

public:
    explicit statistiquef(QWidget *parent = nullptr);
    ~statistiquef();

private:
    Ui::statistiquef *ui;
};

#endif // STATISTIQUEF_H
