#ifndef MASTERNODECONFIGDIALOG_H
#define MASTERNODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class MasternodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class MasternodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MasternodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:10255", QString privkey="MASTERNODEPRIVKEY");
    ~MasternodeConfigDialog();

private:
    Ui::MasternodeConfigDialog *ui;
};

#endif // MASTERNODECONFIGDIALOG_H
