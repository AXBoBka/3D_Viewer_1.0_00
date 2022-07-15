#ifndef GLVIEW_H
#define GLVIEW_H

#include <QtWidgets/QWidget>
#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class glView; }
QT_END_NAMESPACE

class glView : public QOpenGLWidget
{
    Q_OBJECT

public:
    glView(QWidget *parent = nullptr);
    ~glView();
//    void initializeGL();
//    void resizeGL(int w, int h);
//    void paintGL();
private:
    Ui::glView *ui;
};
#endif // GLVIEW_H
