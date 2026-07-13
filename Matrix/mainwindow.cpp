#include "mainwindow.h"
#include "../ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(3, 3, this);

    ui->matrixTable->setModel(model);

    ui->matrixTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->matrixTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(model, &QStandardItemModel::itemChanged, this, &MainWindow::onItemChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_resizeMatrix_clicked()
{
    int matrixSize = ui->matrixSize->value();
    model->setColumnCount(matrixSize);
    model->setRowCount(matrixSize);
}


void MainWindow::on_randomFill_clicked()
{
    int a = ui->spinBox->value();
    int b = ui->spinBox_2->value();
    if (a == 0 && b == 0){
        QMessageBox::critical(this, "Ошибка", "Недопустимый диапазон (0; 0)");
        return;
    }
    if (a > b){
        qSwap(a,b);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(a, b);

    for (int i = 0; i < model->rowCount(); ++i) {
        for (int j = 0; j < model->columnCount(); ++j){

            int randomNumber = dist(gen);
            while (randomNumber == 0){
                randomNumber = dist(gen);
            }

            QStandardItem* item = model->item(i, j);
            if (item){
                model->item(i,j)->setText(QString::number(randomNumber));
            }
            else{
                model->setItem(i, j, new QStandardItem(QString::number(randomNumber)));
            }
        }
    }
}

void MainWindow::on_clearMatrix_clicked()
{
    for (int i = 0; i < model->rowCount(); ++i) {
        for (int j = 0; j < model->columnCount(); ++j) {
            model->setItem(i, j, new QStandardItem(""));
        }
    }
}

void MainWindow::onItemChanged(QStandardItem *item)
{
    QString text = item->text().trimmed();
    bool ok;

    int value = text.toInt(&ok);
    if (!ok || value > 1000 || value < -1000) {
        model->blockSignals(true);

        item->setText("0");

        model->blockSignals(false);
    }
}

void MainWindow::on_calculate_clicked()
{
    long long result = 1;
    bool overflow, noElements;
    result = calculateMatrixProduct(model, overflow, noElements);
    if (overflow){
        QMessageBox::critical(this, "Ошибка", "Переполнение типа");
        return;
    }
    if (noElements){
        QMessageBox::critical(this, "Ошибка", "Нет элементов ниже главной диагонали");
        return;
    }
    ui->result->setText(QString::number(result));
}


long long calculateMatrixProduct(QStandardItemModel *model, bool& overflow, bool& noElements)
{
    overflow = false;
    noElements = false;
    long long result = 1;
    if (model->rowCount() <= 1){
        // QMessageBox::critical(this, "Ошибка", "Нет элементов ниже главной диагонали");
        noElements = true;
        return result;
    }
    for (int row = 0; row < model->rowCount(); ++row){
        for (int col = 0; col < model->columnCount(); ++col){
            if (result > 9223372036854774 || result < -9223372036854774){
                // QMessageBox::critical(this, "Ошибка", "Переполнение типа");
                // return;
                overflow = true;
                return result;
            }
            QStandardItem* item = model->item(row,col);
            if (!item){
                model->setItem(row, col, new QStandardItem("0"));
            }
            else{
                if (item->text().isEmpty()){
                    item->setText("0");
                }
            }
            if (col < row){
                result *= model->item(row, col)->text().toInt();
            }
        }
    }
    return result;
}
