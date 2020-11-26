#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      rhoComboBox(new QComboBox()),
      thetaComboBox(new QComboBox()),
      thresholdComboBox(new QComboBox()),
      canny1ComboBox(new QComboBox()),
      canny2ComboBox(new QComboBox()),
      btnFile(new QPushButton("file")),
      btnDir(new QPushButton("working dir")),
      btnStart(new QPushButton("start")),
      leFile(new QLineEdit()),
      leDir(new QLineEdit()),
      pbarVideo(new QProgressBar())
{
    setGeometry(QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        QSize(400, 150),
        qApp->desktop()->availableGeometry()
    ));
    setWindowTitle("Home Assignment #2");

    // form for the drop-downs
    QFormLayout *formLayout = new QFormLayout();

    rhoComboBox->addItems({"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"});
    thetaComboBox->addItems({"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"});
    thresholdComboBox->addItems({"10", "20", "30", "40", "50", "60", "70", "80", "90", "100"});
    canny1ComboBox->addItems({"50", "75", "100"});
    canny2ComboBox->addItems({"150", "175", "200"});

    formLayout->addRow("Rho:", rhoComboBox);
    formLayout->addRow("Theta:", thetaComboBox);
    formLayout->addRow("Threshold:", thresholdComboBox);
    formLayout->addRow("Canny 1st:", canny1ComboBox);
    formLayout->addRow("Canny 2nd:", canny2ComboBox);

    // grid for selecting target file and target working directory
    QGridLayout *targetsGrid = new QGridLayout();

    leFile->setEnabled(false);
    leDir->setEnabled(false);

    targetsGrid->addWidget(btnFile, 0, 0);
    targetsGrid->addWidget(leFile, 0, 1);
    targetsGrid->addWidget(btnDir, 1, 0);
    targetsGrid->addWidget(leDir, 1, 1);

    // combining all controls together in one layout
    pbarVideo->setEnabled(false);
    QVBoxLayout *vLayout = new QVBoxLayout(this);

    vLayout->addLayout(formLayout);
    vLayout->addLayout(targetsGrid);
    vLayout->addSpacing(15);
    vLayout->addWidget(pbarVideo);
    vLayout->addSpacing(15);
    vLayout->addWidget(btnStart);

    setLayout(vLayout);

    // setting signal handlers
    connect(btnStart, &QPushButton::clicked, this, &MainWindow::onStartButtonClick);
    connect(btnFile, &QPushButton::clicked, this, &MainWindow::onFileButtonClick);
    connect(btnDir, &QPushButton::clicked, this, &MainWindow::onDirButtonClick);

    connect(this, &MainWindow::updateProgressBar, pbarVideo, &QProgressBar::setValue);
}

// it either enables the progressbar and disables everything or vice versa
void MainWindow::enableControls(bool mode) {
    rhoComboBox->setEnabled(mode);
    thetaComboBox->setEnabled(mode);
    thresholdComboBox->setEnabled(mode);
    canny1ComboBox->setEnabled(mode);
    canny2ComboBox->setEnabled(mode);
    btnFile->setEnabled(mode);
    btnDir->setEnabled(mode);
    btnStart->setEnabled(mode);

    pbarVideo->setEnabled(!mode);
}

void MainWindow::onStartButtonClick() {
    // check target directory (existence, emptiness)
    const QFileInfo workDirInfo(leDir->text());
    if(!workDirInfo.exists() || !workDirInfo.isDir() || !workDirInfo.isWritable()) {
        QMessageBox::warning(this, "error", "Bad directory!");
        return;
    }

    // disable all except the progressbar
    enableControls(false);

    // calculate (updating progressbar)
    std::string fileName = leFile->text().toStdString();
    std::string dirName = leDir->text().toStdString();

    double rho = rhoComboBox->currentText().toDouble();
    double theta = thetaComboBox->currentText().toDouble();
    int threshold = thresholdComboBox->currentText().toInt();
    int canny1st = canny1ComboBox->currentText().toInt();
    int canny2nd = canny2ComboBox->currentText().toInt();

    try {
        calculate(fileName, dirName, rho, theta, threshold, canny1st, canny2nd);
    } catch (const LDBadFileException& e) {
        QMessageBox::warning(this, "error", QString("bad file: ") + QString(e.what()));
        enableControls(true);
        return;
    }

    // show finishing popup
    QMessageBox::information(this, "status", "done");

    // enable all except the progressbar
    enableControls(true);
}

void MainWindow::onFileButtonClick() {
    QString fileName = QFileDialog::getOpenFileName(this);
    leFile->setText(fileName);
}

void MainWindow::onDirButtonClick() {
    QString dirName = QFileDialog::getExistingDirectory(this);
    leDir->setText(dirName);
}

MainWindow::~MainWindow()
{
}

