#ifndef QEXTENDEDTABLEWIDGET_H
#define QEXTENDEDTABLEWIDGET_H

#include <QTableWidget>

class QToolButton;
class QLabel;

class QExtendedTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit QExtendedTableWidget(QWidget *parent = nullptr);

    //hide the column in the select button
    void disableColumnForSelection(const int columnCount);

    //overwrite functions
    virtual void setHorizontalHeaderItem(int column, QTableWidgetItem *item);
    virtual bool setColumnHidden(int column, bool hide);

    QList<int> getCurrentVisibleColumns();


protected:
    void resizeEvent(QResizeEvent *);

private:
    QToolButton *mSelectColumnBtn; //use toolBtn istead of pushBtn cause pushBtn does not center the text if menu-indicator is hidden
    QMenu *mButtonMenu;
    QLabel *mMenuHeadlineLabel;
    QList<int> mColumnsDisabledForSelection;

    void updateSelectableColumns();

signals:
    void visibleColumnsChanged();


};

#endif // QEXTENDEDTABLEWIDGET_H
