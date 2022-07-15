#ifndef GLVIEW_H
#define GLVIEW_H

#include <QtWidgets/QWidget>
#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>

#ifdef __cplusplus
extern "C"
{
#endif
#include "../s21_3D_Viewer.h"
#ifdef __cpluplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class glView; }
QT_END_NAMESPACE

class glView : public QOpenGLWidget
{
    Q_OBJECT

public:
    glView(QWidget *parent = nullptr);
    ~glView();
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
      void helloWorld();

private:
    Ui::glView *ui;

//private_slots:

};
#endif // GLVIEW_H
