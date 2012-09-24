#include "dictinfo.hh"
#include "langcoder.hh"
#include "language.hh"
#include "fsencoding.hh"
#include <QString>

DictInfo::DictInfo( QWidget *parent )
{
  ui.setupUi( this );
}

void DictInfo::showInfo( sptr<Dictionary::Class> dict )
{
  setWindowTitle( QString::fromUtf8( dict->getName().data(), dict->getName().size() ) );

  ui.dictionaryTotalArticles->setText( QString::number( dict->getArticleCount() ) );
  ui.dictionaryTotalWords->setText( QString::number( dict->getWordCount() ) );
  ui.dictionaryTranslatesFrom->setText( Language::localizedStringForId( dict->getLangFrom() ) );
  ui.dictionaryTranslatesTo->setText( Language::localizedStringForId( dict->getLangTo() ) );

  std::vector< std::string > const & filenames = dict->getDictionaryFilenames();

  QString filenamesText;

  for( unsigned x = 0; x < filenames.size(); x++ )
  {
    filenamesText += FsEncoding::decode( filenames[ x ].c_str() );
    filenamesText += '\n';
  }

  ui.dictionaryFileList->setPlainText( filenamesText );

  QString info = dict->getDescription();

  if( !info.isEmpty() && info.compare( "NONE" ) != 0 )
    ui.infoLabel->setPlainText( info );
  else
    ui.infoLabel->clear();
}
