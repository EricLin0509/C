CC=clang
CFLAGS=-O3 -Wall -Werror -g -flto=thin -falign-functions=32 -lcrypt -march=native
PO_DIR=locales
LANG=zh_CN
LIBS=data.c hashmap.c
BINS=main

all: $(BINS)

%: %.c $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^
	msgfmt -o $(PO_DIR)/$(LANG)/LC_MESSAGES/management.mo $(PO_DIR)/$(LANG)/LC_MESSAGES/management.po

gen_template: $(PO_DIR)/template.pot

$(PO_DIR)/template.pot: main.c data.c
	mkdir -p $(PO_DIR)
	xgettext -o $(PO_DIR)/template.pot $^ --from-code UTF-8
	mkdir -p $(PO_DIR)/$(LANG)/LC_MESSAGES
	msgmerge --no-fuzzy-matching --update $(PO_DIR)/$(LANG)/LC_MESSAGES/management.po $(PO_DIR)/template.pot
	rm -f $(PO_DIR)/$(LANG)/LC_MESSAGES/management.po~

clean:
	rm -rf *.dSYM *.so *.a *.o $(BINS) $(PO_DIR)/*.pot $(PO_DIR)/*/LC_MESSAGES/*.mo