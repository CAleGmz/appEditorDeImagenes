#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QImage filtroR(const QImage &archEntrada);
    QImage filtroAm(const QImage &archEntrada);
    QImage filtroBn(const QImage &archEntrada);
    QImage brillo(const QImage &archEntrada, int b);
    QImage saturacion(const QImage &archEntrada, int b);
    QImage corrimiento(const QImage &archEntrada, int o, int r, int g, int b);
    QImage operadores(const QImage &archEntrada, int o, int r, int g, int b);


private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButtonFiltro1_clicked();

    void on_pushButtonFiltro2_clicked();

    void on_pushButtonFiltro3_clicked();

    void on_pushButtonFiltro4_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_checkBox_clicked();

    void on_sliderComparar_sliderMoved(int position);

    void on_sliderBOperador_valueChanged(int value);

    void on_sliderROperador_valueChanged(int value);

    void on_sliderGOperador_valueChanged(int value);

    void on_sliderRCorrimientro_valueChanged(int value);

    void on_sliderGCorrimientro_valueChanged(int value);

    void on_sliderBCorrimientro_valueChanged(int value);

    void on_radioButton_toggled(bool checked);

private:
    Ui::Dialog *ui;

    QString path;

};
#endif // DIALOG_H
