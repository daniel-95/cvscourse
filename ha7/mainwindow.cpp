#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent),
	btnFile(new QPushButton("file")),
	btnDir(new QPushButton("working dir")),
	btnStart(new QPushButton("start")),
	leFile(new QLineEdit()),
	leDir(new QLineEdit()),
	nfComboBox(new QComboBox()),
	wsComboBox(new QComboBox()),
	pbarVideo(new QProgressBar())
{
	setGeometry(QStyle::alignedRect(
				Qt::LeftToRight,
				Qt::AlignCenter,
				QSize(400, 150),
				qApp->desktop()->availableGeometry()
				));
	setWindowTitle("Home Assignment #7");
	// form for the drop-downs
	QFormLayout *formLayout = new QFormLayout();

	nfComboBox->addItems({"5", "10", "25", "50", "100"});
	wsComboBox->addItems({"5", "7", "9", "11", "13", "15", "17", "19", "21"});

	formLayout->addRow("Number of frames:", nfComboBox);
	formLayout->addRow("Windiw size:", wsComboBox);
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

	int nFrames = nfComboBox->currentText().toInt();
	int nWinSize = wsComboBox->currentText().toInt();

	try {
		calculate(fileName, dirName, nFrames, nWinSize);
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

