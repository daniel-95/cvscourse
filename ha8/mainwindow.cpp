#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent),
	btnFile(new QPushButton("file")),
	btnDir(new QPushButton("working dir")),
	btnModelFile(new QPushButton("model file")),
	btnModelMetaFile(new QPushButton("metadata file")),
	btnStart(new QPushButton("start")),

	leFile(new QLineEdit()),
	leDir(new QLineEdit()),
	leModelFile(new QLineEdit()),
	leModelMetaFile(new QLineEdit()),

	pbarVideo(new QProgressBar())
{
	setGeometry(QStyle::alignedRect(
				Qt::LeftToRight,
				Qt::AlignCenter,
				QSize(400, 150),
				qApp->desktop()->availableGeometry()
				));
	setWindowTitle("Home Assignment #8");

	// grid for selecting target file and target working directory
	QGridLayout *targetsGrid = new QGridLayout();

	leFile->setEnabled(false);
	leDir->setEnabled(false);
	leModelFile->setEnabled(false);
	leModelMetaFile->setEnabled(false);

	targetsGrid->addWidget(btnFile, 0, 0);
	targetsGrid->addWidget(leFile, 0, 1);
	targetsGrid->addWidget(btnDir, 1, 0);
	targetsGrid->addWidget(leDir, 1, 1);
	targetsGrid->addWidget(btnModelFile, 2, 0);
	targetsGrid->addWidget(leModelFile, 2, 1);
	targetsGrid->addWidget(btnModelMetaFile, 3, 0);
	targetsGrid->addWidget(leModelMetaFile, 3, 1);

	// combining all controls together in one layout
	pbarVideo->setEnabled(false);
	QVBoxLayout *vLayout = new QVBoxLayout(this);

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
	connect(btnModelFile, &QPushButton::clicked, this, &MainWindow::onModelFileButtonClick);
	connect(btnModelMetaFile, &QPushButton::clicked, this, &MainWindow::onModelMetaFileButtonClick);

	connect(this, &MainWindow::updateProgressBar, pbarVideo, &QProgressBar::setValue);
}

// it either enables the progressbar and disables everything or vice versa
void MainWindow::enableControls(bool mode) {
	btnFile->setEnabled(mode);
	btnDir->setEnabled(mode);
	btnStart->setEnabled(mode);
	btnModelFile->setEnabled(mode);
	btnModelMetaFile->setEnabled(mode);

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
	std::string modelFile = leModelFile->text().toStdString();
	std::string modelMetaFile = leModelMetaFile->text().toStdString();

	try {
		calculate(fileName, dirName, modelFile, modelMetaFile);
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

void MainWindow::onModelFileButtonClick() {
	QString fileName = QFileDialog::getOpenFileName(this);
	leModelFile->setText(fileName);
}

void MainWindow::onModelMetaFileButtonClick() {
	QString fileName = QFileDialog::getOpenFileName(this);
	leModelMetaFile->setText(fileName);
}

MainWindow::~MainWindow()
{
}

