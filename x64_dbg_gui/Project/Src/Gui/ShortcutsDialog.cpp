#include "ShortcutsDialog.h"
#include "ui_ShortcutsDialog.h"

ShortcutsDialog::ShortcutsDialog(QWidget* parent) : QDialog(parent), ui(new Ui::ShortcutsDialog)
{
    ui->setupUi(this);
    //set window flags
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    setWindowFlags(Qt::Dialog | Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);
#endif
    setFixedSize(this->size()); //fixed size
    setModal(true);

    // x64 has no model-view-controler pattern
    QStringList tblHeader;
    tblHeader << "Instruction" << "Shortcut";

    currentRow = 0;

    ui->tblShortcuts->setColumnCount(2);
    ui->tblShortcuts->verticalHeader()->setVisible(false);
    ui->tblShortcuts->setHorizontalHeaderLabels(tblHeader);
    ui->tblShortcuts->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblShortcuts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblShortcuts->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblShortcuts->setShowGrid(false);
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    ui->tblShortcuts->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
#else
    ui->tblShortcuts->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
#endif

    ui->tblShortcuts->verticalHeader()->setDefaultSectionSize(15);

    const unsigned int numShortcuts = Config()->Shortcuts.count();
    ui->tblShortcuts->setRowCount(numShortcuts);
    int j = 0;
    for(QMap<QString, Configuration::Shortcut>::iterator i = Config()->Shortcuts.begin(); i != Config()->Shortcuts.end(); ++i, j++)
    {
        QTableWidgetItem* shortcutName = new QTableWidgetItem(i.value().Name);
        QTableWidgetItem* shortcutKey = new QTableWidgetItem(i.value().Hotkey.toString(QKeySequence::NativeText));
        ui->tblShortcuts->setItem(j, 0, shortcutName);
        ui->tblShortcuts->setItem(j, 1, shortcutKey);
    }

    connect(ui->tblShortcuts, SIGNAL(itemSelectionChanged()), this, SLOT(syncTextfield()));
    connect(ui->shortcutEdit, SIGNAL(askForSave()), this, SLOT(updateShortcut()));
    connect(this, SIGNAL(rejected()), this, SLOT(rejectedSlot()));
}

void ShortcutsDialog::updateShortcut()
{
    const QKeySequence newKey = ui->shortcutEdit->getKeysequence();
    if(newKey != currentShortcut.Hotkey)
    {
        bool good = true;
        if(!newKey.isEmpty())
        {
            int idx = 0;
            for(QMap<QString, Configuration::Shortcut>::iterator i = Config()->Shortcuts.begin(); i != Config()->Shortcuts.end(); ++i, idx++)
            {
                if(i.value().Name == currentShortcut.Name) //skip current shortcut in list
                    continue;
                if(i.value().GlobalShortcut && i.value().Hotkey == newKey) //newkey is trying to override a global shortcut
                {
                    good = false;
                    break;
                }
                else if(currentShortcut.GlobalShortcut && i.value().Hotkey == newKey) //current shortcut is global and overrides another local hotkey
                {
                    ui->tblShortcuts->setItem(idx, 1, new QTableWidgetItem(""));
                    Config()->setShortcut(i.key(), QKeySequence());
                }
            }
        }
        if(good)
        {
            for(QMap<QString, Configuration::Shortcut>::iterator i = Config()->Shortcuts.begin(); i != Config()->Shortcuts.end(); ++i)
            {
                if(i.value().Name == currentShortcut.Name)
                {
                    Config()->setShortcut(i.key(), newKey);
                    break;
                }
            }
            QString keyText = "";
            if(!newKey.isEmpty())
                keyText = newKey.toString(QKeySequence::NativeText);
            ui->tblShortcuts->item(currentRow, 1)->setText(keyText);
            ui->shortcutEdit->setErrorState(false);
        }
        else
        {
            ui->shortcutEdit->setErrorState(true);
        }
    }
}

void ShortcutsDialog::syncTextfield()
{
    QModelIndexList indexes = ui->tblShortcuts->selectionModel()->selectedRows();
    if(indexes.count() < 1)
        return;
    currentRow = indexes.at(0).row();
    for(QMap<QString, Configuration::Shortcut>::iterator i = Config()->Shortcuts.begin(); i != Config()->Shortcuts.end(); ++i)
    {
        if(i.value().Name == ui->tblShortcuts->item(currentRow, 0)->text())
        {
            currentShortcut = i.value();
            break;
        }
    }
    ui->shortcutEdit->setErrorState(false);
    ui->shortcutEdit->setText(currentShortcut.Hotkey.toString(QKeySequence::NativeText));
    ui->shortcutEdit->setFocus();
}

ShortcutsDialog::~ShortcutsDialog()
{
    delete ui;
}

void ShortcutsDialog::on_btnSave_clicked()
{
    Config()->writeShortcuts();
    GuiAddStatusBarMessage("Settings saved!\n");
}

void ShortcutsDialog::rejectedSlot()
{
    Config()->readShortcuts();
}
