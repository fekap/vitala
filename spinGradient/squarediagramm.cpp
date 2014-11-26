#include "squarediagramm.h"
#include "ui_squarediagramm.h"
#include <QPainter>
#include <math.h>

SquareDiagramm::SquareDiagramm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SquareDiagramm)
{
    ui->setupUi(this);
    m_data = new QList<LatticePoint>();
}

void SquareDiagramm::setLatticeSize(unsigned int latticeSize)
{
    this->m_latticeSize=latticeSize;
}

void SquareDiagramm::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    paint(painter);
}

void SquareDiagramm::paint(QPainter &painter)
{
    painter.setPen(Qt::black);
    m_boxSize=qMin(this->width(), this->height())-1;
    QRect r1(0, 0, m_boxSize-1, m_boxSize-1);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(r1);


    for (int i = 0; i < m_data->size(); i++)
    {
        LatticePoint point=m_data->at(i);
        int padding = 0;
        double step = (m_boxSize-padding*2)/(m_latticeSize)+0.55;
        double x=point.i*step;
        double y=point.j*step;
        painter.setBrush(QBrush(calculateColor(point.value), Qt::SolidPattern));
        painter.drawRect(x,y,step,step);
    }
}

void SquareDiagramm::saveImage(QString fileName)
{
    QImage img(m_boxSize, m_boxSize, QImage::Format_RGB32);
    QPainter painter(&img);
    paint(painter);
    img.save(fileName);
}

void SquareDiagramm::loadFromFile(QFile &file)
{
    ViData vidata;
    vidata.parse(file);
    m_data = vidata.getPoints();
    m_latticeSize = vidata.getLatticeSize();
    this->repaint();
}

SquareDiagramm::~SquareDiagramm()
{
    delete ui;
}

QColor SquareDiagramm::calculateColor(double value)
{
    int r,g,b;
    if(value>0){
        r=255;
        b=g=(int)round((1-value)*255);
    }
    else{
        b=255;
        r=g=(int)round((1+value)*255);
    }
    return QColor(r,g,b);
}
