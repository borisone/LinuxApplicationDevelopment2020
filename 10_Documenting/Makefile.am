bin_PROGRAMS = guess
pkgdata_DATA = ru/LC_MESSAGES/guess.mo

@DX_RULES@

ru/LC_MESSAGES/guess.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

messages.pot: guess.pot guess.c
		xgettext -k_ -c guess.c -o messages.new.pot
		cp guess.pot messages.pot
		msgmerge -U messages.pot messages.new.pot

ru.po: messages.pot
	msgmerge -U $@ $<

gitclean:
	git clean -fd

clean:
	rm -rf ru/ ru_RU/ messages.new.pot messages.pot

