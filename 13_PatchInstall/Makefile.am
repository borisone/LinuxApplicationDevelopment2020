bin_PROGRAMS = guess
pkgdata_DATA = ru/LC_MESSAGES/guess.mo
pkgdatadir = $(localedir)/ru/LC_MESSAGES
AM_CFLAGS = -D LOCALEDIR='"$(localedir)"'

ru/LC_MESSAGES/guess.mo: ru.po
	mkdir ru/LC_MESSAGES/ -p
	msgfmt ru.po -o ru/LC_MESSAGES/guess.mo

messages.pot: guess.pot guess.c
		xgettext -k_ -c guess.c -o messages.new.pot
		cp guess.pot messages.pot
		msgmerge -U messages.pot messages.new.pot

ru.po: messages.pot
	msgmerge -U $@ $<

gitclean:
	git clean -fd

clean:
	rm -rf ru/LC_MESSAGES/guess.mo messages.new.pot messages.pot

