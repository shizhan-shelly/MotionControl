// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef PAGES_CONSUMABLESMAP_H__
#define PAGES_CONSUMABLESMAP_H__

typedef std::pair<std::string, std::string> pair_t;

static const pair_t consumables_pairs[] = {
  pair_t("", ""),

};

static const std::map<std::string, std::string> CONSUMABLES_MAP(
    consumables_pairs,
    consumables_pairs +
    sizeof(consumables_pairs) / sizeof(consumables_pairs[0]));

#endif // PAGES_CONSUMABLESMAP_H__
