#include "glview.h"
#include "ui_glview.h"

glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::glView)
{

}

glView::~glView()
{
    delete ui;
}

void glView::initializeGL() {

}

void glView::resizeGL(int w, int h) {


}

void glView::paintGL() {
    t_data data_Obj = {0, 0, {nullptr, 0, 0}, 0};
    char str[1000] = "/Users/acoustic/Desktop/3D_viewer_1.0_00/src/3D_models(OBJ)/easyCube.obj";
    int ret = s21_3D_Viewer(str, &data_Obj);
    if (!ret) {

    }

}

//void MainScene::mousePressEvent(QMouseEvent *event)
//{
//    pressPosition = event->pos();
//}
//void MainScene::mouseMoveEvent(QMouseEvent *event)
//{
//    xAxisRotation += (180 * ((GLfloat)event->y() - (GLfloat)pressPosition.y())) / (currentHeight);
//    yAxisRotation += (180 * ((GLfloat)event->x() - (GLfloat)pressPosition.x())) / (currentWidth);
//    pressPosition = event->pos();
//    updateGL();
//}
