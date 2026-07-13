#include <QTest>
#include "../mainwindow.h"
#include "../functions.h"
// add necessary includes here

class MatrixTest : public QObject
{
    Q_OBJECT

public:
    MatrixTest();
    ~MatrixTest() override;




private slots:
    void test_case1();
    void testNormalCalculation();
    void testZeroUnderDiagonal();
    void testSingleRowMatrix();
    void testOverflow();
    void testEmptyCells();
};

MatrixTest::MatrixTest() {}

MatrixTest::~MatrixTest() = default;

void MatrixTest::test_case1() {}

void MatrixTest::testNormalCalculation() {
    QStandardItemModel *model = new QStandardItemModel(3, 3);

    model->setItem(0, 0, new QStandardItem("1"));
    model->setItem(0, 1, new QStandardItem("2"));
    model->setItem(0, 2, new QStandardItem("3"));

    model->setItem(1, 0, new QStandardItem("4"));
    model->setItem(1, 1, new QStandardItem("5"));
    model->setItem(1, 2, new QStandardItem("6"));

    model->setItem(2, 0, new QStandardItem("7"));
    model->setItem(2, 1, new QStandardItem("8"));
    model->setItem(2, 2, new QStandardItem("9"));

    bool overflow = false;
    bool noElements = false;
    long long res = calculateMatrixProduct(model, overflow, noElements);
    long long expectedRes = 224;

    QVERIFY(!overflow);
    QVERIFY(!noElements);
    QCOMPARE(res, expectedRes);
}

void MatrixTest::testZeroUnderDiagonal() {
    QStandardItemModel *model = new QStandardItemModel(2, 2);

    model->setItem(0, 0, new QStandardItem("1"));
    model->setItem(0, 1, new QStandardItem("2"));
    model->setItem(1, 0, new QStandardItem("0"));
    model->setItem(1, 1, new QStandardItem("3"));

    bool overflow = false, noElements = false;
    long long res = calculateMatrixProduct(model, overflow, noElements);
    long long expectedRes = 0;
    QCOMPARE(res, expectedRes);
}

void MatrixTest::testSingleRowMatrix() {
    QStandardItemModel *model = new QStandardItemModel(1, 1);

    model->setItem(0, 0, new QStandardItem("5"));

    bool overflow = false, noElements = false;
    calculateMatrixProduct(model, overflow, noElements);

    QVERIFY2(noElements == true, "Распознавание 1x1 матрицы или нульмерной");
}

void MatrixTest::testOverflow() {
    QStandardItemModel *model = new QStandardItemModel(3, 3);

    model->setItem(0, 0, new QStandardItem("1"));
    model->setItem(0, 1, new QStandardItem("1"));
    model->setItem(0, 2, new QStandardItem("1"));

    model->setItem(1, 0, new QStandardItem("1000000"));
    model->setItem(1, 1, new QStandardItem("1"));
    model->setItem(1, 2, new QStandardItem("1"));

    model->setItem(2, 0, new QStandardItem("1000000"));
    model->setItem(2, 1, new QStandardItem("1000000"));
    model->setItem(2, 2, new QStandardItem("1"));

    bool overflow = false, noElements = false;
    calculateMatrixProduct(model, overflow, noElements);

    QVERIFY2(overflow == true, "Распознавание переполнения типа");
}

void MatrixTest::testEmptyCells()
{
    QStandardItemModel *model = new QStandardItemModel(2, 2);

    model->setItem(0, 0, new QStandardItem("5"));
    model->setItem(1, 0, new QStandardItem("2"));

    bool overflow = false, noElements = false;
    long long res = calculateMatrixProduct(model, overflow, noElements);
    long long expectedRes = 2;

    QCOMPARE(res, expectedRes);
}

QTEST_APPLESS_MAIN(MatrixTest)

#include "tst_matrixtest.moc"
