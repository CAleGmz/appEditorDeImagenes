#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->label->setScaledContents(true);

    ui->widgetEditar->setEnabled(true);
    ui->widgetEditar->setVisible(true);
    ui->widgetEfectos->setVisible(false);
    ui->widgetEfectos->setEnabled(false);
    ui->widgetMejora->setEnabled(false);
    ui->widgetMejora->setVisible(false);

    ui->sliderROperador->setEnabled(true);
    ui->sliderGOperador->setEnabled(true);
    ui->sliderBOperador->setEnabled(true);
    ui->sliderRCorrimientro->setEnabled(false);
    ui->sliderGCorrimientro->setEnabled(false);
    ui->sliderBCorrimientro->setEnabled(false);

    ui->sliderComparar->setVisible(false);
    ui->sliderComparar->setEnabled(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);

    connect(ui->sliderROperador, SIGNAL(valueChanged(int)), ui->lcdROperador, SLOT(display(int)));
    connect(ui->sliderGOperador, SIGNAL(valueChanged(int)), ui->lcdGOperador, SLOT(display(int)));
    connect(ui->sliderBOperador, SIGNAL(valueChanged(int)), ui->lcdBOperador, SLOT(display(int)));
    connect(ui->sliderRCorrimientro, SIGNAL(valueChanged(int)), ui->lcdRCorrimiento, SLOT(display(int)));
    connect(ui->sliderGCorrimientro, SIGNAL(valueChanged(int)), ui->lcdGCorrimiento, SLOT(display(int)));
    connect(ui->sliderBCorrimientro, SIGNAL(valueChanged(int)), ui->lcdBCorrimiento, SLOT(display(int)));

    QPixmap filtroIcon1 (":/new/prefix1/flitoEjIcon.jpeg");
    QIcon botonIcon1(filtroIcon1);
    ui->pushButtonFiltro1->setIcon(botonIcon1);
    ui->pushButtonFiltro1->setIconSize(filtroIcon1.rect().size());

    QPixmap filtroIcon2 (":/new/prefix1/flitoEjAmIcon.jpeg");
    QIcon botonIcon2(filtroIcon2);
    ui->pushButtonFiltro2->setIcon(botonIcon2);
    ui->pushButtonFiltro2->setIconSize(filtroIcon2.rect().size());

    QPixmap filtroIcon3 (":/new/prefix1/flitoEjRIcon.jpeg");
    QIcon botonIcon3(filtroIcon3);
    ui->pushButtonFiltro3->setIcon(botonIcon3);
    ui->pushButtonFiltro3->setIconSize(filtroIcon3.rect().size());

    QPixmap filtroIcon4 (":/new/prefix1/flitoEjBnIcon.jpeg");
    QIcon botonIcon4(filtroIcon4);
    ui->pushButtonFiltro4->setIcon(botonIcon4);
    ui->pushButtonFiltro4->setIconSize(filtroIcon4.rect().size());

    path = ":/new/prefix1/higgsch.jpeg";

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QFileDialog dialogo(this);
    dialogo.setNameFilter("Imagenes(*.png *.bmp *.jpg *.jpeg *.gif)");
    dialogo.setViewMode(QFileDialog::Detail);
    QString nomatch = QFileDialog::getOpenFileName(this, "Abrir Imagen", "C:\\Users\\Ale\\Downloads",
                                                           tr("Imagen (*.png *.xpm *.jpg *.bmp *.jpeg *.gif)"));


    if(!nomatch.isEmpty()){
        path = nomatch;
        QImage imagen(nomatch);
        ui->label->setPixmap(QPixmap::fromImage(imagen));
        ui->label->setScaledContents(true);
    }
}

QImage Dialog::filtroR(const QImage &archEntrada)
{
    QImage archSalida(archEntrada.size(), archEntrada.format());
    for (int ren =0; ren < archEntrada.height(); ren++) {
        const QRgb *pixelEntrada = reinterpret_cast<const QRgb*>(archEntrada.scanLine(ren));
        QRgb *pixelSalida  = reinterpret_cast<QRgb*>(archSalida.scanLine(ren));
        for(int col=0;col<archEntrada.width();col++){
            //Extraer la tonalidad correspondiente
            int rojo = qRed(pixelEntrada[col]);
            //int verde = qGreen(pixelEntrada[col]);
            //int azul = qBlue(pixelEntrada[col]);
            int alpha = qAlpha(pixelEntrada[col]);

            pixelSalida[col] = qRgba(rojo, rojo/2, rojo/3,alpha);
        }
    }
    return archSalida;
}

QImage Dialog::filtroBn(const QImage &archEntrada)
{
    QImage archSalida(archEntrada.size(), archEntrada.format());
    for (int ren =0; ren < archEntrada.height(); ren++) {
        const QRgb *pixelEntrada = reinterpret_cast<const QRgb*>(archEntrada.scanLine(ren));
        QRgb *pixelSalida  = reinterpret_cast<QRgb*>(archSalida.scanLine(ren));
        for(int col=0;col<archEntrada.width();col++){
            //Extraer la tonalidad correspondiente
            int rojo = qRed(pixelEntrada[col]);
            //int verde = qGreen(pixelEntrada[col]);
            //int azul = qBlue(pixelEntrada[col]);
            int alpha = qAlpha(pixelEntrada[col]);

            pixelSalida[col] = qRgba(rojo,rojo,rojo,alpha);
        }
    }
    return archSalida;
}

QImage Dialog::filtroAm(const QImage &archEntrada)
{
    QImage archSalida(archEntrada.size(), archEntrada.format());
    for (int ren =0; ren < archEntrada.height(); ren++) {
        const QRgb *pixelEntrada = reinterpret_cast<const QRgb*>(archEntrada.scanLine(ren));
        QRgb *pixelSalida  = reinterpret_cast<QRgb*>(archSalida.scanLine(ren));
        for(int col=0;col<archEntrada.width();col++){
            //Extraer la tonalidad correspondiente
            int rojo = qRed(pixelEntrada[col]);
            int verde = qGreen(pixelEntrada[col]);
            //int azul = qBlue(pixelEntrada[col]);
            int alpha = qAlpha(pixelEntrada[col]);

            pixelSalida[col] = qRgba(rojo,verde,0,alpha);
        }
    }
    return archSalida;
}

QImage Dialog::brillo(const QImage &archEntrada, int b)
{
    QImage archSalida(archEntrada.size(), archEntrada.format());
    for (int ren =0; ren < archEntrada.height(); ren++) {
        const QRgb *pixelEntrada = reinterpret_cast<const QRgb*>(archEntrada.scanLine(ren));
        QRgb *pixelSalida  = reinterpret_cast<QRgb*>(archSalida.scanLine(ren));
        for(int col=0;col<archEntrada.width();col++){
            //Extraer la tonalidad correspondiente
            int rojo = qRed(pixelEntrada[col]);
            int verde = qGreen(pixelEntrada[col]);
            int azul = qBlue(pixelEntrada[col]);
            int alpha = qAlpha(pixelEntrada[col]);

            if(rojo>200 && verde>200 && azul >200)
                pixelSalida[col] = qRgba(rojo,verde,azul,alpha);
            else
                if(rojo<50 && verde<50 && azul <50)
                    pixelSalida[col] = qRgba(rojo,verde,azul,alpha);
                else
                    if(b<0 && rojo<40 || verde<40 || azul <40)
                        pixelSalida[col] = qRgba(rojo,verde,azul,alpha);
                    else
                        pixelSalida[col] = qRgba(rojo+b,verde+b,azul+b,alpha);
        }
    }
    return archSalida;
}

QImage Dialog::saturacion(const QImage &archEntrada, int s)
{
    QImage archSalida(archEntrada.size(), archEntrada.format());
    for (int ren =0; ren < archEntrada.height(); ren++) {
        const QRgb *pixelEntrada = reinterpret_cast<const QRgb*>(archEntrada.scanLine(ren));
        QRgb *pixelSalida  = reinterpret_cast<QRgb*>(archSalida.scanLine(ren));
        for(int col=0;col<archEntrada.width();col++){
            //Extraer la tonalidad correspondiente
            int rojo = qRed(pixelEntrada[col]);
            int verde = qGreen(pixelEntrada[col]);
            int azul = qBlue(pixelEntrada[col]);
            int alpha = qAlpha(pixelEntrada[col]);

            if(rojo>verde && rojo>azul && rojo < 220)
                pixelSalida[col] = qRgba(rojo + s,verde,azul,alpha);
            else
                if(verde>rojo && verde>azul && verde < 220)
                    pixelSalida[col] = qRgba(rojo,verde + s,azul,alpha);
                else
                    if(azul>rojo && azul>verde && azul < 220)
                        pixelSalida[col] = qRgba(rojo,verde,azul + s,alpha);
                    else
                        if(s<0)
                            pixelSalida[col] = qRgba(rojo,rojo,rojo,alpha);
                        else
                            pixelSalida[col] = qRgba(rojo,verde,azul,alpha);
        }
    }
    return archSalida;
}

QImage Dialog::corrimiento(const QImage &archEntrada,int o, int r, int g, int b)
{
    QImage archSalida(archEntrada.size(), archEntrada.format());
    for (int ren =0; ren < archEntrada.height(); ren++) {
        const QRgb *pixelEntrada = reinterpret_cast<const QRgb*>(archEntrada.scanLine(ren));
        QRgb *pixelSalida  = reinterpret_cast<QRgb*>(archSalida.scanLine(ren));
        for(int col=0;col<archEntrada.width();col++){
            //Extraer la tonalidad correspondiente
            int rojo = qRed(pixelEntrada[col]);
            int verde = qGreen(pixelEntrada[col]);
            int azul = qBlue(pixelEntrada[col]);
            int alpha = qAlpha(pixelEntrada[col]);

            if(o == 0){
                rojo = rojo<<r;
                verde= verde<<g;
                azul = azul<<b;
            }else{
                rojo = rojo>>r;
                verde = verde>>g;
                azul = azul>>b;
            }

            pixelSalida[col] = qRgba(rojo,verde,azul,alpha);
        }
    }
        return archSalida;
}

QImage Dialog::operadores(const QImage &archEntrada, int o, int r, int g, int b)
{
    QImage archSalida(archEntrada.size(), archEntrada.format());
    for (int ren =0; ren < archEntrada.height(); ren++) {
        const QRgb *pixelEntrada = reinterpret_cast<const QRgb*>(archEntrada.scanLine(ren));
        QRgb *pixelSalida  = reinterpret_cast<QRgb*>(archSalida.scanLine(ren));
        for(int col=0;col<archEntrada.width();col++){
            //Extraer la tonalidad correspondiente
            int rojo = qRed(pixelEntrada[col]);
            int verde = qGreen(pixelEntrada[col]);
            int azul = qBlue(pixelEntrada[col]);
            int alpha = qAlpha(pixelEntrada[col]);

            switch (o) {
            case 0:
                rojo = rojo & r;
                verde = verde & g;
                azul = azul & b;
                break;
            case 1:
                rojo = rojo | r;
                verde = verde | g;
                azul = azul | b;
                break;
            case 2:
                rojo = rojo ^ r;
                verde = verde ^ g;
                azul = azul ^ b;
                break;
            }


            pixelSalida[col] = qRgba(rojo,verde,azul,alpha);
        }
    }
    return archSalida;
}

void Dialog::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->widgetEditar->setEnabled(true);
        ui->widgetEditar->setVisible(true);

        ui->widgetEfectos->setEnabled(false);
        ui->widgetEfectos->setVisible(false);

        ui->widgetMejora->setEnabled(false);
        ui->widgetMejora->setVisible(false);
        break;
    case 1:
        ui->widgetEfectos->setEnabled(true);
        ui->widgetEfectos->setVisible(true);

        ui->widgetEditar->setEnabled(false);
        ui->widgetEditar->setVisible(false);

        ui->widgetMejora->setEnabled(false);
        ui->widgetMejora->setVisible(false);
        break;

    case 2:
        ui->widgetMejora->setEnabled(true);
        ui->widgetMejora->setVisible(true);

        ui->widgetEditar->setEnabled(false);
        ui->widgetEditar->setVisible(false);

        ui->widgetEfectos->setEnabled(false);
        ui->widgetEfectos->setVisible(false);
        break;
    }
}

void Dialog::on_pushButtonFiltro1_clicked()
{
    QImage imagen(path);
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}

void Dialog::on_pushButtonFiltro2_clicked()
{
    QImage imagen(path);
    imagen = filtroAm(imagen);
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}

void Dialog::on_pushButtonFiltro3_clicked()
{
    QImage imagen(path);
    imagen = filtroR(imagen);
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}

void Dialog::on_pushButtonFiltro4_clicked()
{
    QImage imagen(path);
    imagen = filtroBn(imagen);
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}


void Dialog::on_horizontalSlider_2_valueChanged(int value)
{
    QImage imagen(path);
    imagen = brillo(imagen,value);
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}


void Dialog::on_horizontalSlider_3_valueChanged(int value)
{
    QImage imagen(path);
    imagen = saturacion(imagen,value);
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}


void Dialog::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()){
        ui->sliderComparar->setVisible(true);
        ui->sliderComparar->setEnabled(true);
        ui->label_2->setVisible(true);
        QImage imagen(path);
        QImage imagen2 = imagen.scaled(541,401,Qt::IgnoreAspectRatio);
        ui->label_2->setPixmap(QPixmap::fromImage(imagen2));
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
    }else{
        ui->sliderComparar->setVisible(false);
        ui->sliderComparar->setEnabled(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
    }
}


void Dialog::on_sliderComparar_sliderMoved(int position)
{
    ui->label_2->setGeometry(ui->label_2->x(),ui->label_2->y(), position, ui->label_2->height());

    if(position == 0){
        ui->label_3->setVisible(false);
        ui->label_4->move(ui->label->x() + ui->label->width()/2-50, ui->label_4->y());
    }else
        if(position < 150){
            ui->label_3->setVisible(true);
            ui->label_4->setVisible(true);
            ui->label_3->move(ui->label->x() + 15, ui->label_4->y());
            ui->label_4->move(ui->label->x() + ui->label->width()/2-50, ui->label_4->y());
        }else
            if(position > 350 && position < 539){
                ui->label_3->setVisible(true);
                ui->label_4->setVisible(true);
                ui->label_3->move(ui->label->x() + ui->label->width()/2, ui->label_4->y());
                ui->label_4->move(ui->label->x() + + ui->label->width()-85, ui->label_4->y());
            }
            else
                if(position > 540){
                    ui->label_4->setVisible(false);
                    ui->label_3->move(ui->label->x() + ui->label->width()/2, ui->label_4->y());
                }else{
                    ui->label_3->setVisible(true);
                    ui->label_4->setVisible(true);
                    ui->label_3->move(220, 0);
                    ui->label_4->move(490, 0);
                }
}


void Dialog::on_sliderROperador_valueChanged(int value)
{
    QImage imagen(path);
    imagen = operadores(imagen,ui->comboBox_2->currentIndex(), value, ui->sliderGOperador->value(), ui->sliderBOperador->value());
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}

void Dialog::on_sliderGOperador_valueChanged(int value)
{
    QImage imagen(path);
    imagen = operadores(imagen,ui->comboBox_2->currentIndex(), ui->sliderROperador->value(), value, ui->sliderBOperador->value());
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}

void Dialog::on_sliderBOperador_valueChanged(int value)
{
    QImage imagen(path);
    imagen = operadores(imagen,ui->comboBox_2->currentIndex(), ui->sliderROperador->value(), ui->sliderGOperador->value(), value);
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}


void Dialog::on_sliderRCorrimientro_valueChanged(int value)
{
    QImage imagen(path);
    imagen = operadores(imagen,ui->comboBox_3->currentIndex(), value, ui->sliderGCorrimientro->value(), ui->sliderBCorrimientro->value());
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}

void Dialog::on_sliderGCorrimientro_valueChanged(int value)
{
    QImage imagen(path);
    imagen = operadores(imagen,ui->comboBox_3->currentIndex(), ui->sliderRCorrimientro->value(), value, ui->sliderBCorrimientro->value());
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}

void Dialog::on_sliderBCorrimientro_valueChanged(int value)
{
    QImage imagen(path);
    imagen = operadores(imagen,ui->comboBox_3->currentIndex(), ui->sliderRCorrimientro->value(), ui->sliderGCorrimientro->value(), value);
    ui->label->setPixmap(QPixmap::fromImage(imagen));
    ui->label->setScaledContents(true);
}


void Dialog::on_radioButton_toggled(bool checked)
{
    if(checked){
        ui->sliderROperador->setEnabled(true);
        ui->sliderGOperador->setEnabled(true);
        ui->sliderBOperador->setEnabled(true);

        ui->sliderRCorrimientro->setEnabled(false);
        ui->sliderGCorrimientro->setEnabled(false);
        ui->sliderBCorrimientro->setEnabled(false);
    }else{
        ui->sliderROperador->setEnabled(false);
        ui->sliderGOperador->setEnabled(false);
        ui->sliderBOperador->setEnabled(false);

        ui->sliderRCorrimientro->setEnabled(true);
        ui->sliderGCorrimientro->setEnabled(true);
        ui->sliderBCorrimientro->setEnabled(true);
    }
}

