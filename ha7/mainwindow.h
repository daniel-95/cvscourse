#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileInfo>
#include <QtWidgets>

#include <exception>
#include <string>

class MainWindow : public QWidget
{
Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	private slots:
		void onStartButtonClick();
	void onFileButtonClick();
	void onDirButtonClick();

signals:
	void updateProgressBar(int value);

private:
	void enableControls(bool mode);
	void calculate(std::string fileName, std::string dirName, int nFrames, int nWinSize);

	QPushButton *btnFile;
	QPushButton *btnDir;
	QPushButton *btnStart;

	QComboBox *nfComboBox;
	QComboBox *wsComboBox;

	QLineEdit *leFile;
	QLineEdit *leDir;

	QProgressBar *pbarVideo;
};

class LDBadFileException : public std::exception {
private:
	std::string fileName;

public:
	LDBadFileException(const std::string& fileName) : fileName(fileName) {}

	const char* what() const noexcept {
		return fileName.c_str();
	}
};

#endif // MAINWINDOW_H
