#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include <random>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:


    void on_resizeMatrix_clicked();

    void on_randomFill_clicked();

    void on_clearMatrix_clicked();

    void onItemChanged(QStandardItem* item);

    void on_calculate_clicked();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *model;
};


long long calculateMatrixProduct(QStandardItemModel *model, bool& overflow, bool& noElements);



#endif // MAINWINDOW_H
