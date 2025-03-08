#include "Gui.hpp"
#include <QTextEdit>
#include <QMenuBar>
#include <QLayout>
#include <QAction>
#include <QResizeEvent>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
std::string OperatorWindow::getFilePathViaDialog(){
    QString filePath = QFileDialog::getOpenFileName(
        this,                                          // Parent widget
        tr("Open File"),                               // Dialog title
        QDir::currentPath(),                           // Initial directory (e.g., user's home)
        tr("All Files (*.*);;Blockchain files (*.bc)") // File filters
    );
    std::string str = filePath.toStdString();
    int pos = str.find_last_of("/");
    std::cout << pos << std::endl;
    str = str.substr(pos + 1);
    return str;
}

BlockchainWindow::BlockchainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Blockchain Project GUI");
    resize(800, 600);
    // Create a text edit widget as the central widget.
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QHBoxLayout *button2Layout = new QHBoxLayout;
    fileButton = new QPushButton("Open blockchain from file");
    newBlockchainButton = new QPushButton("Create new blockchain");
    buttonLayout->addWidget(fileButton);
    button2Layout->addWidget(newBlockchainButton);
    layout->addLayout(buttonLayout);
    layout->addLayout(button2Layout);
    connect(fileButton, &QPushButton::clicked, this, &BlockchainWindow::openFileButton);
    connect(newBlockchainButton,&QPushButton::clicked, this, &BlockchainWindow::createNewButton);
    connect(this, &BlockchainWindow::resizeEvent, this, &BlockchainWindow::resizeButtons);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void BlockchainWindow::createNewButton(){
    blockchain = BlockChain();
    OperatorWindow *r = new OperatorWindow(nullptr, blockchain, hash);
    r->show();
    this->hide();
}

OperatorWindow::OperatorWindow(QWidget *parent, BlockChain blockchain, SHA_256_HASHER hash)
    : QMainWindow(parent), blockchain(blockchain), hash(hash), algo(&this->hash, &this->blockchain)
{
    resize(800, 600);
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QPushButton *getFileLastHashButton = new QPushButton("Get file's last hash");
    QPushButton *getFileHashesButton = new QPushButton("Get file's hashes");
    QPushButton *addFileToBlockButton = new QPushButton("Add file to block");
    QPushButton *getBlockSeralizedButton = new QPushButton("Get block serialized");
    QPushButton *createNewBlockButton = new QPushButton("Create new block");
    QPushButton *saveBlockchainButton = new QPushButton("Save blockchain");

    connect(getFileLastHashButton, &QPushButton::clicked, this, &OperatorWindow::getFileLastHash);
    connect(getFileHashesButton, &QPushButton::clicked, this, &OperatorWindow::getFileHashes);
    connect(addFileToBlockButton, &QPushButton::clicked, this, &OperatorWindow::addFileToBlock);
    connect(getBlockSeralizedButton, &QPushButton::clicked, this, &OperatorWindow::getBlockSeralized);
    connect(createNewBlockButton, &QPushButton::clicked, this, &OperatorWindow::createBlock);
    connect(saveBlockchainButton, &QPushButton::clicked, this, &OperatorWindow::saveBlockchain);

    layout->addWidget(getFileLastHashButton);
    layout->addWidget(getFileHashesButton);
    layout->addWidget(addFileToBlockButton);
    layout->addWidget(getBlockSeralizedButton);
    layout->addWidget(createNewBlockButton);
    layout->addWidget(saveBlockchainButton);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void BlockchainWindow::openFileButton()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,                                          // Parent widget
        tr("Open File"),                               // Dialog title
        QDir::currentPath(),                           // Initial directory (e.g., user's home)
        tr("All Files (*.*);;Blockchain files (*.bc)") // File filters
    );
    File f(filePath.toStdString());
    blockchain = des.deserialize(f.read(), &hash);
    OperatorWindow *r = new OperatorWindow(nullptr, blockchain, hash);
    r->show();
    this->hide();
}


TextWindow::TextWindow(const QString &text, QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Text Window");
    resize(800, 600);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(text, this);
    QPushButton *closeButton = new QPushButton("Close", this);

    layout->addWidget(label);
    layout->addWidget(closeButton);

    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    setLayout(layout);
}

void OperatorWindow::getFileLastHash()
{
    std::string str = getFilePathViaDialog();
    std::cout << "\"" << str << "\"" << std::endl;
    std::vector<unsigned char> vstr(str.begin(), str.end());
    std::vector<unsigned char> fileNameHash = this->hash.hash(vstr);
    std::vector<unsigned char> vHash = algo.getFileLastHash(fileNameHash);
    std::string sHash = hash.hashToHex(vHash);
    QString Hash = QString::fromStdString(sHash);
    TextWindow *textWindows = new TextWindow(Hash, nullptr);
    textWindows->exec();
}

void OperatorWindow::getFileHashes()
{
    std::string str = getFilePathViaDialog();
    std::cout << "\"" << str << "\"" << std::endl;
    std::vector<unsigned char> vstr(str.begin(), str.end());
    std::vector<unsigned char> fileNameHash = this->hash.hash(vstr);
    std::vector<std::vector<unsigned char>> vHash = algo.getFileHashes(fileNameHash);
    std::string sHash = "";
    for (auto &i : vHash)
    {
        sHash += hash.hashToHex(i);
        sHash += "\n";
    }
    std::cout << sHash;
    QString Hash = QString::fromStdString(sHash);
    TextWindow *textWindows = new TextWindow(Hash, this);
    textWindows->exec();
}

void OperatorWindow::addFileToBlock()
{
    std::string str = getFilePathViaDialog();
    std::cout << "\"" << str << "\"" << std::endl;
    std::cout << algo.addFileToBlock(str) << std::endl;
}

void OperatorWindow::createBlock()
{
    std::cout << algo.createNewBlock() << std::endl;
}

void OperatorWindow::getBlockSeralized()
{
    bool ok;
    int blockChainSize = this->blockchain.getLength();
    std::string S = "Please enter an integer (max = " + std::to_string(blockChainSize - 1) + "):";
    QString qS = QString::fromStdString(S);
    int id = QInputDialog::getInt(this, "Enter a number", qS,
                                  0,       // Default value
                                  0, 1000, // Min & Max range
                                  1,       // Step size
                                  &ok);    // Pointer to check if the user pressed OK or Cancel
    if (ok)
    {
        std::string text = algo.getBlockSerialized(id);
        QString s = QString::fromStdString(text);
        TextWindow *w = new TextWindow(s, this);
        w->exec();
    }
}

void OperatorWindow::saveBlockchain()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,                                          // Parent widget
        tr("Open File"),                               // Dialog title
        QDir::currentPath(),                           // Initial directory (e.g., user's home)
        tr("All Files (*.*);;Blockchain files (*.bc)") // File filters
    );
    std::string str = filePath.toStdString();
    algo.saveBlockchain(str);
}

void BlockchainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    resizeButtons();
}

void BlockchainWindow::resizeButtons()
{
    int buttonWidth = this->width() * 0.7;
    fileButton->setMinimumWidth(buttonWidth);
    fileButton->setMaximumWidth(buttonWidth);
    newBlockchainButton->setMinimumWidth(buttonWidth);
    newBlockchainButton->setMaximumWidth(buttonWidth);
}