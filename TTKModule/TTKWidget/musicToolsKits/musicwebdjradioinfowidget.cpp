#include "musicwebdjradioinfowidget.h"
#include "musicdjradioprogramcategoryrequest.h"
#include "musicsettingmanager.h"
#include "musicdownloadsourcerequest.h"

#include <qmath.h>

MusicWebDJRadioInfoTableWidget::MusicWebDJRadioInfoTableWidget(QWidget *parent)
    : MusicItemQueryTableWidget(parent)
{

}

MusicWebDJRadioInfoTableWidget::~MusicWebDJRadioInfoTableWidget()
{
    clearAllItems();
}

void MusicWebDJRadioInfoTableWidget::setQueryInput(MusicAbstractQueryRequest *query)
{
    MusicItemQueryTableWidget::setQueryInput(query);
    if(parent()->metaObject()->indexOfSlot("queryAllFinished()") != -1)
    {
        connect(m_downLoadManager, SIGNAL(downLoadDataChanged(QString)), parent(), SLOT(queryAllFinished()));
    }
}



MusicWebDJRadioInfoWidget::MusicWebDJRadioInfoWidget(QWidget *parent)
    : MusicAbstractItemQueryWidget(parent)
{
    delete m_statusLabel;
    m_statusLabel = nullptr;

    m_queryTableWidget = new MusicWebDJRadioInfoTableWidget(this);
    m_queryTableWidget->hide();

    MusicDJRadioProgramCategoryRequest *v = new MusicDJRadioProgramCategoryRequest(this);
    m_queryTableWidget->setQueryInput(v);
    connect(v, SIGNAL(createCategoryInfoItem(MusicResultsItem)), SLOT(createCategoryInfoItem(MusicResultsItem)));
}

void MusicWebDJRadioInfoWidget::setSongName(const QString &name)
{
    MusicAbstractItemQueryWidget::setSongName(name);
    m_queryTableWidget->startSearchQuery(name);
}

void MusicWebDJRadioInfoWidget::setSongNameById(const QString &id)
{
    Q_UNUSED(id);
}

void MusicWebDJRadioInfoWidget::resizeWindow()
{
    m_queryTableWidget->resizeWindow();
    if(!m_resizeWidgets.isEmpty())
    {
        int width = M_SETTING_PTR->value(MusicSettingManager::WidgetSize).toSize().width();
            width = width - WINDOW_WIDTH_MIN + 390;

        QLabel *label = m_resizeWidgets[0];
        label->setText(MusicUtils::Widget::elidedText(label->font(), label->toolTip(), Qt::ElideRight, width));

        label = m_resizeWidgets[1];
        label->setText(MusicUtils::Widget::elidedText(label->font(), label->toolTip(), Qt::ElideRight, width));

        label = m_resizeWidgets[2];
        label->setText(MusicUtils::Widget::elidedText(label->font(), label->toolTip(), Qt::ElideRight, width));

        label = m_resizeWidgets[3];
        label->setText(MusicUtils::Widget::elidedText(label->font(), label->toolTip(), Qt::ElideRight, width));
    }
}

void MusicWebDJRadioInfoWidget::queryAllFinished()
{
    setSongCountText();
}

void MusicWebDJRadioInfoWidget::createCategoryInfoItem(const MusicResultsItem &item)
{
    m_currentPlaylistItem = item;

    createLabels();

    if(!m_resizeWidgets.isEmpty())
    {
        MusicDownloadSourceRequest *download = new MusicDownloadSourceRequest(this);
        connect(download, SIGNAL(downLoadRawDataChanged(QByteArray)), SLOT(downLoadFinished(QByteArray)));
        if(!item.m_coverUrl.isEmpty() && item.m_coverUrl != COVER_URL_NULL)
        {
            download->startToDownload(item.m_coverUrl);
        }

        QLabel *label = m_resizeWidgets[0];
        label->setToolTip(item.m_name);
        label->setText(MusicUtils::Widget::elidedText(label->font(), label->toolTip(), Qt::ElideRight, 390));

        label = m_resizeWidgets[1];
        label->setToolTip(tr("Singer: %1").arg(item.m_nickName));
        label->setText(MusicUtils::Widget::elidedText(label->font(), label->toolTip(), Qt::ElideRight, 390));

        label = m_resizeWidgets[2];
        label->setToolTip(tr("PlayCount: %1").arg(item.m_playCount));
        label->setText(MusicUtils::Widget::elidedText(label->font(), label->toolTip(), Qt::ElideRight, 390));

        label = m_resizeWidgets[3];
        label->setToolTip(tr("UpdateTime: %1").arg(item.m_updateTime));
        label->setText(MusicUtils::Widget::elidedText(label->font(), label->toolTip(), Qt::ElideRight, 390));
    }
}

void MusicWebDJRadioInfoWidget::createLabels()
{
    initFirstWidget();
    m_container->show();

    layout()->removeWidget(m_mainWindow);
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->verticalScrollBar()->setStyleSheet(MusicUIObject::MQSSScrollBarStyle01);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setAlignment(Qt::AlignLeft);
    scrollArea->setWidget(m_mainWindow);
    layout()->addWidget(scrollArea);

    QWidget *function = new QWidget(m_mainWindow);
    function->setStyleSheet(MusicUIObject::MQSSCheckBoxStyle01 + MusicUIObject::MQSSPushButtonStyle03);
    QVBoxLayout *grid = new QVBoxLayout(function);

    QWidget *firstTopFuncWidget = new QWidget(function);
    QHBoxLayout *firstTopFuncLayout = new QHBoxLayout(firstTopFuncWidget);
    QLabel *firstLabel = new QLabel(function);
    firstLabel->setText(tr("<font color=#158FE1> DJRadio > %1 </font>").arg(m_currentPlaylistItem.m_name));
    QPushButton *backButton = new QPushButton(tr("Back"));
    backButton->setFixedSize(90, 30);
    backButton->setStyleSheet(MusicUIObject::MQSSPushButtonStyle03);
    backButton->setCursor(QCursor(Qt::PointingHandCursor));
    connect(backButton, SIGNAL(clicked()), this, SIGNAL(backToMainMenu()));
    firstTopFuncLayout->addWidget(firstLabel);
    firstTopFuncLayout->addWidget(backButton);
    grid->addWidget(firstTopFuncWidget);
    //
    QWidget *topFuncWidget = new QWidget(function);
    QHBoxLayout *topFuncLayout = new QHBoxLayout(topFuncWidget);

    m_iconLabel = new QLabel(topFuncWidget);
    m_iconLabel->setPixmap(QPixmap(":/image/lb_warning").scaled(180, 180));
    m_iconLabel->setFixedSize(210, 180);
    //

    QWidget *topLineWidget = new QWidget(topFuncWidget);
    QVBoxLayout *topLineLayout = new QVBoxLayout(topLineWidget);
    topLineLayout->setContentsMargins(10, 5, 5, 0);
    QLabel *nameLabel = new QLabel(topLineWidget);
    QFont nameFont = nameLabel->font();
    nameFont.setPixelSize(20);
    nameLabel->setFont(nameFont);
    nameLabel->setStyleSheet(MusicUIObject::MQSSFontStyle01);
    nameLabel->setText("-");
    QLabel *singerLabel = new QLabel(topLineWidget);
    singerLabel->setStyleSheet(MusicUIObject::MQSSColorStyle04 + MusicUIObject::MQSSFontStyle03);
    singerLabel->setText("-");
    QLabel *playCountLabel = new QLabel(topLineWidget);
    playCountLabel->setStyleSheet(MusicUIObject::MQSSColorStyle04 + MusicUIObject::MQSSFontStyle03);
    QLabel *updateTimeLabel = new QLabel(topLineWidget);
    updateTimeLabel->setStyleSheet(MusicUIObject::MQSSColorStyle04 + MusicUIObject::MQSSFontStyle03);
    updateTimeLabel->setText("-");

    topLineLayout->addWidget(nameLabel);
    topLineLayout->addWidget(singerLabel);
    topLineLayout->addWidget(playCountLabel);
    topLineLayout->addWidget(updateTimeLabel);
    topLineWidget->setLayout(topLineLayout);

    topFuncLayout->addWidget(m_iconLabel);
    topFuncLayout->addWidget(topLineWidget);
    topFuncWidget->setLayout(topFuncLayout);
    grid->addWidget(topFuncWidget);

    //
    QWidget *functionWidget = new QWidget(this);
    functionWidget->setStyleSheet(MusicUIObject::MQSSPushButtonStyle03);
    QHBoxLayout *hlayout = new QHBoxLayout(functionWidget);
    m_songButton = new QPushButton(functionWidget);
    m_songButton->setText(tr("songItems"));
    m_songButton->setFixedSize(100, 25);
    m_songButton->setCursor(QCursor(Qt::PointingHandCursor));
    hlayout->addWidget(m_songButton);
    hlayout->addStretch(1);
    functionWidget->setLayout(hlayout);
    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(m_songButton, 0);
    connect(group, SIGNAL(buttonClicked(int)), m_container, SLOT(setCurrentIndex(int)));

#ifdef Q_OS_UNIX
    m_songButton->setFocusPolicy(Qt::NoFocus);
#endif
    grid->addWidget(functionWidget);

    //
    grid->addWidget(m_container);
    grid->addStretch(1);

    function->setLayout(grid);
    m_mainWindow->layout()->addWidget(function);

    m_resizeWidgets << nameLabel << singerLabel << playCountLabel << updateTimeLabel;
}
