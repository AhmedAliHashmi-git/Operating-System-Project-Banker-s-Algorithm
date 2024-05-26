#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
#include <QMessageBox>
#include <algorithm>
#include <random>

class BankersAlgoWindow : public QMainWindow {
public:
    BankersAlgoWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        auto centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        auto layout = new QGridLayout(centralWidget);

        // Allocation Table
        auto allocationTableLabel = new QLabel("Allocation Table", this);
        layout->addWidget(allocationTableLabel, 0, 0);
        allocationTable = new QTableWidget(this); // No initial rows specified
        allocationTable->setColumnCount(4); // 4 columns
        allocationTable->setHorizontalHeaderLabels(QStringList() << "Process" << "A" << "B" << "C");
        allocationTable->setShowGrid(false); // Remove gridlines
        allocationTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Set size policy
        layout->addWidget(allocationTable, 1, 0);

        // Max Allocation Table
        auto maxAllocationTableLabel = new QLabel("Max Allocation Table", this);
        layout->addWidget(maxAllocationTableLabel, 0, 1);
        maxAllocationTable = new QTableWidget(this); // No initial rows specified
        maxAllocationTable->setColumnCount(4); // 4 columns
        maxAllocationTable->setHorizontalHeaderLabels(QStringList() << "A" << "B" << "C" << "");
        maxAllocationTable->setShowGrid(false); // Remove gridlines
        maxAllocationTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Set size policy
        layout->addWidget(maxAllocationTable, 1, 1);

        // Need Matrix
        auto needMatrixLabel = new QLabel("Need Matrix", this);
        layout->addWidget(needMatrixLabel, 2, 0);
        needTable = new QTableWidget(this); // No initial rows specified
        needTable->setColumnCount(3); // 3 columns
        needTable->setHorizontalHeaderLabels(QStringList() << "A" << "B" << "C");
        needTable->setShowGrid(false); // Remove gridlines
        needTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Set size policy
        layout->addWidget(needTable, 3, 0);

        // Available Table
        auto availableTableLabel = new QLabel("Available Resources", this);
        layout->addWidget(availableTableLabel, 2, 1);
        availableTable = new QTableWidget(this); // No initial rows specified
        availableTable->setColumnCount(3); // 3 columns
        availableTable->setHorizontalHeaderLabels(QStringList() << "A" << "B" << "C");
        availableTable->setShowGrid(false); // Remove gridlines
        availableTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Set size policy
        layout->addWidget(availableTable, 3, 1);

        // Safe Sequence
        auto safeSequenceLabel = new QLabel("Safe Sequence", this);
        layout->addWidget(safeSequenceLabel, 0, 2);
        // Assuming Safe Sequence as a Label for simplicity
        auto safeSequence = new QLabel("Sequence here", this);
        layout->addWidget(safeSequence, 1, 2);

        // Process Name
        auto processNameLabel = new QLabel("Process Name", this);
        layout->addWidget(processNameLabel, 4, 0);
        processNameLineEdit = new QLineEdit(this);
        processNameLineEdit->setPlaceholderText("Process Name");
        layout->addWidget(processNameLineEdit, 4, 1);
        r1LineEdit = new QLineEdit(this);
        r1LineEdit->setPlaceholderText("R1");
        layout->addWidget(r1LineEdit, 4, 2);
        r2LineEdit = new QLineEdit(this);
        r2LineEdit->setPlaceholderText("R2");
        layout->addWidget(r2LineEdit, 4, 3);
        r3LineEdit = new QLineEdit(this);
        r3LineEdit->setPlaceholderText("R3");
        layout->addWidget(r3LineEdit, 4, 4);
        addProcessButton = new QPushButton("Add Process", this);
        layout->addWidget(addProcessButton, 4, 5);

        // Max Width
        auto maxWidthLabel = new QLabel("Max matrix", this);
        layout->addWidget(maxWidthLabel, 5, 0);
        r1MaxWidthLineEdit = new QLineEdit(this);
        r1MaxWidthLineEdit->setPlaceholderText("R1");
        layout->addWidget(r1MaxWidthLineEdit, 5, 1);
        r2MaxWidthLineEdit = new QLineEdit(this);
        r2MaxWidthLineEdit->setPlaceholderText("R2");
        layout->addWidget(r2MaxWidthLineEdit, 5, 2);
        r3MaxWidthLineEdit = new QLineEdit(this);
        r3MaxWidthLineEdit->setPlaceholderText("R3");
        layout->addWidget(r3MaxWidthLineEdit, 5, 3);
        addMaxWidthButton = new QPushButton("Add Max Width", this);
        layout->addWidget(addMaxWidthButton, 5, 4);

        // Mama Resources
        auto mamaResourcesLabel = new QLabel("Max Resources", this);
        layout->addWidget(mamaResourcesLabel, 6, 0);
        r1MamaLineEdit = new QLineEdit(this);
        r1MamaLineEdit->setPlaceholderText("R1");
        layout->addWidget(r1MamaLineEdit, 6, 1);
        r2MamaLineEdit = new QLineEdit(this);
        r2MamaLineEdit->setPlaceholderText("R2");
        layout->addWidget(r2MamaLineEdit, 6, 2);
        r3MamaLineEdit = new QLineEdit(this);
        r3MamaLineEdit->setPlaceholderText("R3");
        layout->addWidget(r3MamaLineEdit, 6, 3);

        // Insertion Fields and Add Button
        auto addProcessFields = new QWidget(this);
        auto fieldsLayout = new QHBoxLayout(addProcessFields);
        fieldsLayout->addWidget(processNameLabel);
        fieldsLayout->addWidget(processNameLineEdit);
        fieldsLayout->addWidget(r1LineEdit);
        fieldsLayout->addWidget(r2LineEdit);
        fieldsLayout->addWidget(r3LineEdit);
        fieldsLayout->addWidget(addProcessButton);
        layout->addWidget(addProcessFields, 7, 0, 1, 3);

        // Calculate Button
        auto calculateButton = new QPushButton("Calculate", this);
        layout->addWidget(calculateButton, 8, 2);

        // Styling
        calculateButton->setStyleSheet("background-color: blue; color: white;");
        setWindowTitle("BankersAlgo");
        resize(800, 600); // Set window size
        // Connect add process button click to slot
        connect(addProcessButton, &QPushButton::clicked, this, &BankersAlgoWindow::addProcessClicked);
        connect(addMaxWidthButton, &QPushButton::clicked, this, &BankersAlgoWindow::addMaxAllocationClicked);
        connect(calculateButton, &QPushButton::clicked, this, &BankersAlgoWindow::calculateClicked);
        // Styling
        addProcessButton->setStyleSheet("background-color: blue; color: white;");
        setWindowTitle("BankersAlgo");
        resize(800, 600); // Set window size
    }

private slots:
    void calculateClicked() {
        // Get the allocation matrix
        QVector<QVector<int>> allocationMatrix;
        for (int row = 0; row < allocationTable->rowCount(); ++row) {
            QVector<int> allocationRow;
            for (int col = 1; col < allocationTable->columnCount(); ++col) {
                allocationRow.append(allocationTable->item(row, col)->text().toInt());
            }
            allocationMatrix.append(allocationRow);
        }

        // Get the max allocation matrix
        QVector<QVector<int>> maxAllocationMatrix;
        for (int row = 0; row < maxAllocationTable->rowCount(); ++row) {
            QVector<int> maxAllocationRow;
            for (int col = 0; col < maxAllocationTable->columnCount() - 1; ++col) {
                maxAllocationRow.append(maxAllocationTable->item(row, col)->text().toInt());
            }
            maxAllocationMatrix.append(maxAllocationRow);
        }

        // Calculate the need matrix
        QVector<QVector<int>> needMatrix;
        for (int i = 0; i < allocationMatrix.size(); ++i) {
            QVector<int> needRow;
            for (int j = 0; j < allocationMatrix[i].size(); ++j) {
                int need = maxAllocationMatrix[i][j] - allocationMatrix[i][j];
                needRow.append(need);
            }
            needMatrix.append(needRow);
        }
        // Update the need matrix table
        // Update the need matrix table in the GUI
        needTable->setRowCount(needMatrix.size());
        needTable->setColumnCount(needMatrix[0].size());
        for (int i = 0; i < needMatrix.size(); ++i) {
            for (int j = 0; j < needMatrix[i].size(); ++j) {
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(needMatrix[i][j]));
                needTable->setItem(i, j, item);
            }
        }

        // Calculate available resources
        QVector<int> totalAllocation(allocationMatrix[0].size(), 0);
        QVector<int> maxResources(maxAllocationMatrix[0].size(), 0);

        // Calculate total allocation for each resource type
        for (const auto& row : allocationMatrix) {
            for (int i = 0; i < row.size(); ++i) {
                totalAllocation[i] += row[i];
            }
        }

        // Calculate total maximum resources for each resource type
        for (const auto& row : maxAllocationMatrix) {
            for (int i = 0; i < row.size(); ++i) {
                maxResources[i] += row[i];
            }
        }

        // Get mama resources
        int mamaR1 = r1MamaLineEdit->text().toInt();
        int mamaR2 = r2MamaLineEdit->text().toInt();
        int mamaR3 = r3MamaLineEdit->text().toInt();

        // Calculate available resources using the formula
        QVector<int> availableResources = {mamaR1, mamaR2, mamaR3};
        for (int i = 0; i < allocationMatrix.size(); ++i) {
            for (int j = 0; j < allocationMatrix[i].size(); ++j) {
                availableResources[j] -= allocationMatrix[i][j];
            }
        }

        // Check if available resources are negative and adjust if necessary
        for (int i = 0; i < availableResources.size(); ++i) {
            if (availableResources[i] < 0) {
                QMessageBox::warning(this, "Limit Exceeded", "Limit exceeded for resource " + QString::number(i + 1));
                return;
            }
        }
        // Calculate safe sequence
        QVector<int> safeSequence = calculateSafeSequence(allocationMatrix, availableResources);

        QVector<int> randomSequence = generateRandomSafeSequence(safeSequence);
        QString sequenceStr = "Safe Sequence: ";
        for (int i = 0; i < randomSequence.size(); ++i) {
            sequenceStr += QString::number(randomSequence[i]);
            if (i != randomSequence.size() - 1) {
                sequenceStr += " -> ";
            }
        }
        QMessageBox::information(this, "Safe Sequence", sequenceStr);



        // Update the available table
        availableTable->setRowCount(1);
        availableTable->setColumnCount(availableResources.size());
        for (int i = 0; i < availableResources.size(); ++i) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(availableResources[i]));
            availableTable->setItem(0, i, item);
        }

        // Set focus back to the main window
        this->setFocus();
    }


    void addMaxAllocationClicked() {
        // Get the input values
        QString r1 = r1MaxWidthLineEdit->text();
        QString r2 = r2MaxWidthLineEdit->text();
        QString r3 = r3MaxWidthLineEdit->text();

        // Insert the values into the Max Allocation table
        int row = maxAllocationTable->rowCount();
        maxAllocationTable->insertRow(row);
        maxAllocationTable->setItem(row, 0, new QTableWidgetItem(r1));
        maxAllocationTable->setItem(row, 1, new QTableWidgetItem(r2));
        maxAllocationTable->setItem(row, 2, new QTableWidgetItem(r3));


        // Clear input fields
        r1MaxWidthLineEdit->clear();
        r2MaxWidthLineEdit->clear();
        r3MaxWidthLineEdit->clear();
    }

    void addProcessClicked() {
        // Get the input values
        QString processName = processNameLineEdit->text();
        QString r1 = r1LineEdit->text();
        QString r2 = r2LineEdit->text();
        QString r3 = r3LineEdit->text();

        // Check if adding the new process exceeds the resource limits
        int newR1 = r1.toInt();
        int newR2 = r2.toInt();
        int newR3 = r3.toInt();

        // Get the available resources
        int mamaR1 = r1MamaLineEdit->text().toInt();
        int mamaR2 = r2MamaLineEdit->text().toInt();
        int mamaR3 = r3MamaLineEdit->text().toInt();

        // Calculate total allocation for each resource type
        int totalAllocR1 = 0;
        int totalAllocR2 = 0;
        int totalAllocR3 = 0;
        for (int row = 0; row < allocationTable->rowCount(); ++row) {
            totalAllocR1 += allocationTable->item(row, 1)->text().toInt();
            totalAllocR2 += allocationTable->item(row, 2)->text().toInt();
            totalAllocR3 += allocationTable->item(row, 3)->text().toInt();
        }

        // Calculate available resources
        int availableR1 = mamaR1 - totalAllocR1;
        int availableR2 = mamaR2 - totalAllocR2;
        int availableR3 = mamaR3 - totalAllocR3;

        // Check if adding this process would exceed the available resources
        if (newR1 > availableR1 || newR2 > availableR2 || newR3 > availableR3) {
            QMessageBox::warning(this, "Resource Limit Exceeded", "Adding this process would exceed the available resources!");
            return;
        }

        // Insert the values into the allocation table
        int row = allocationTable->rowCount();
        allocationTable->insertRow(row);
        allocationTable->setItem(row, 0, new QTableWidgetItem(processName));
        allocationTable->setItem(row, 1, new QTableWidgetItem(r1));
        allocationTable->setItem(row, 2, new QTableWidgetItem(r2));
        allocationTable->setItem(row, 3, new QTableWidgetItem(r3));

        // Clear input fields
        processNameLineEdit->clear();
        r1LineEdit->clear();
        r2LineEdit->clear();
        r3LineEdit->clear();
    }

private:
    QTableWidget *allocationTable;
    QTableWidget *maxAllocationTable;
    QTableWidget *needTable;
    QTableWidget *availableTable;
    QLineEdit *processNameLineEdit;
    QLineEdit *r1LineEdit;
    QLineEdit *r2LineEdit;
    QLineEdit *r3LineEdit;
    QLineEdit *r1MaxWidthLineEdit;
    QLineEdit *r2MaxWidthLineEdit;
    QLineEdit *r3MaxWidthLineEdit;
    QLineEdit *r1MamaLineEdit;
    QLineEdit *r2MamaLineEdit;
    QLineEdit *r3MamaLineEdit;
    QPushButton *addProcessButton;
    QPushButton *addMaxWidthButton;

    QVector<int> calculateSafeSequence(const QVector<QVector<int>>& allocation, const QVector<int>& available) {
        int numProcesses = allocation.size();
        QVector<bool> finished(numProcesses, false);
        QVector<int> safeSequence;

        QVector<int> work = available;
        QVector<QVector<int>> need(allocation.size(), QVector<int>(allocation[0].size(), 0));
        for (int i = 0; i < numProcesses; ++i) {
            for (int j = 0; j < allocation[i].size(); ++j) {
                need[i][j] = allocation[i][j];
            }
        }

        int count = 0;
        while (count < numProcesses) {
            bool found = false;
            for (int p = 0; p < numProcesses; ++p) {
                if (!finished[p]) {
                    bool canFinish = true;
                    for (int r = 0; r < work.size(); ++r) {
                        if (need[p][r] > work[r]) {
                            canFinish = false;
                            break;
                        }
                    }
                    if (canFinish) {
                        for (int k = 0; k < work.size(); ++k) {
                            work[k] += allocation[p][k];
                        }
                        safeSequence.push_back(p);
                        finished[p] = true;
                        ++count;
                        found = true;
                    }
                }
            }
            if (!found) {
                break; // No process could satisfy safety condition
            }
        }


        return safeSequence;
    }
    QVector<int> generateRandomSafeSequence(const QVector<int>& safeSequence) {
        QVector<int> randomSequence = safeSequence;

        // Set a fixed seed for reproducibility
        unsigned int seed = 42; // You can choose any integer value as the seed
        std::mt19937 g(seed); // Seed the random number generator

        // Shuffle the safe sequence
        std::shuffle(randomSequence.begin(), randomSequence.end(), g);

        return randomSequence;
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    BankersAlgoWindow w;
    w.show();
    return a.exec();
}

