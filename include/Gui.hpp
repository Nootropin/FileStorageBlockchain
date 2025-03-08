#ifndef GUI_HPP
#define GUI_HPP
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QPushButton>
#include <QFileDialog>
#include <QInputDialog>
#include <QDir>
#include "Hash.hpp"
#include "Deserializer.hpp"
#include "BlockChain.hpp"
#include "BlockChainAlgo.hpp"
#include <iostream>
QT_USE_NAMESPACE
class TextWindow: public QDialog{
    public:
    TextWindow(const QString &text, QWidget *parent);
};

class OperatorWindow : public QMainWindow{
    Q_OBJECT
    public:
        OperatorWindow(QWidget *parent,BlockChain blockchain, SHA_256_HASHER hash);
    private:
        std::string getFilePathViaDialog();
        BlockChain blockchain;
        BlockChainAlgo algo;
        SHA_256_HASHER hash;
    private slots:
        void getFileLastHash();
        void getFileHashes();
        void addFileToBlock();
        void createBlock();
        void getBlockSeralized();
        void saveBlockchain();
};
class BlockchainWindow  : public QMainWindow {
    Q_OBJECT
public:
    BlockchainWindow(QWidget *parent = nullptr);
private:
    QPushButton* fileButton;
    QPushButton* newBlockchainButton;
    BlockChain blockchain;
    SHA_256_HASHER hash;
    Deserializer des;
private slots:
    void openFileButton();
    void createNewButton();
    void resizeEvent(QResizeEvent *event) override;
    void resizeButtons();
};

#endif