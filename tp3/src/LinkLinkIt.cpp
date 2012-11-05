#include "LinkLinkIt.h"

LinkLinkIt::LinkLinkIt(ArbolCategorias& abCat) : _aCategorias(abCat) {
	_infoLinks = new DiccString<InfoLink>();
}

LinkLinkIt::~LinkLinkIt() {
	delete _infoLinks;
}

