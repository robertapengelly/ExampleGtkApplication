#------------------------------------------------------------------------------
# Tool configuration
#------------------------------------------------------------------------------
CC                      ?=  gcc
DEL_FILE                :=  rm -rf
PKGCONFIG               :=  $(shell which pkg-config)

CFLAGS                  :=  $(shell $(PKGCONFIG) --cflags gtk+-3.0)
LIBS                    :=  $(shell $(PKGCONFIG) --libs gtk+-3.0)
#CFLAGS              +=  $(shell pkg-config --libs libxml-2.0 pkg-config --cflags libxml-2.0)

GLIB_COMPILE_RESOURCES  :=  $(shell $(PKGCONFIG) --variable=glib_compile_resources gio-2.0)
GLIB_COMPILE_SCHEMAS    :=  $(shell $(PKGCONFIG) --variable=glib_compile_schemas gio-2.0)

#------------------------------------------------------------------------------
# Display color macros
#------------------------------------------------------------------------------
BLUE                    :=  \033[1;34m
YELLOW                  :=  \033[1;33m
NORMAL                  :=  \033[0m

TAG                     :=  $(BLUE)[notepad++]$(NORMAL)

C_FILES                 :=  $(shell find * -name '*.c')
RES_FILES               :=  resources.c

OBJ_FILES               :=  $(C_FILES:%.c=../out/build_data/%.o) $(RES_FILES:%.c=../out/build_data/%.o)

TARGET                  :=  ../out/release/lib/notepad++-bin

make_launch:
	(mkdir -p "../out/release/bin/" && cp -f "../support_files/launch/notepad++" "../out/release//bin/" && chmod 755 "../out/release/bin/notepad++")

org.gtk.notepadplusplus.gschema.valid: org.gtk.notepadplusplus.gschema.xml
	@echo "$(TAG) Compiling $<"
	@$(GLIB_COMPILE_SCHEMAS) --strict --dry-run --schema-file=$< && mkdir -p $(@D) && touch $@

../out/release/lib/gschemas.compiled: org.gtk.notepadplusplus.gschema.valid
	@$(GLIB_COMPILE_SCHEMAS) .
	@test -d $(shell dirname $@) || mkdir -p $(shell dirname $@)
	@mv gschemas.compiled $@

$(RES_FILES): app.gresource.xml app-menu.ui mainwindow.ui
	@echo "$(TAG) Compiling $<"
	@$(GLIB_COMPILE_RESOURCES) app.gresource.xml --target=$@ --sourcedir=. --generate-source

$(OBJ_FILES): ../out/build_data/%.o: %.c
	@test -d $(shell dirname $@) || mkdir -p $(shell dirname $@)
	@echo "$(TAG) Compiling $<"
	@$(CC) $(CFLAGS) -I../include -c $< -o $@

$(TARGET): make_launch $(OBJ_FILES) ../out/release/lib/gschemas.compiled
	@-$(DEL_FILE) resources.c
	@test -d $(shell dirname $@) || mkdir -p $(shell dirname $@)
	@echo "$(TAG) Linking $(notdir $@)"
	@$(CC) -o $@ $(OBJ_FILES) $(LIBS)

compiler_rcc_clean:
	@-$(DEL_FILE) ../out/build_data/qrc_resources.cpp

compiler_moc_predefs_clean:
	@-$(DEL_FILE) ../out/build_data/moc_predefs.h

compiler_moc_header_clean:
	@-$(DEL_FILE) ../out/build_data/moc_mainwindow.cpp ../out/build_data/moc_topeditorcontainer.cpp ../out/build_data/moc_editortabwidget.cpp ../out/build_data/moc_docengine.cpp ../out/build_data/moc_frmabout.cpp ../out/build_data/moc_notepadqq.cpp ../out/build_data/moc_frmpreferences.cpp ../out/build_data/moc_editor.cpp ../out/build_data/moc_bannerfilechanged.cpp ../out/build_data/moc_bannerbasicmessage.cpp ../out/build_data/moc_bannerfileremoved.cpp ../out/build_data/moc_customqwebview.cpp ../out/build_data/moc_clickablelabel.cpp ../out/build_data/moc_frmencodingchooser.cpp ../out/build_data/moc_bannerindentationdetected.cpp ../out/build_data/moc_frmindentationmode.cpp ../out/build_data/moc_singleapplication.cpp ../out/build_data/moc_frmsearchreplace.cpp ../out/build_data/moc_advancedsearchdock.cpp ../out/build_data/moc_extension.cpp ../out/build_data/moc_frmlinenumberchooser.cpp ../out/build_data/moc_extensionsserver.cpp ../out/build_data/moc_stub.cpp ../out/build_data/moc_runtimesupport.cpp ../out/build_data/moc_windowstub.cpp ../out/build_data/moc_notepadqqstub.cpp ../out/build_data/moc_extensionsloader.cpp ../out/build_data/moc_menuitemstub.cpp ../out/build_data/moc_installextension.cpp ../out/build_data/moc_keygrabber.cpp ../out/build_data/moc_nqqrun.cpp ../out/build_data/moc_filesearcher.cpp ../out/build_data/moc_filereplacer.cpp ../out/build_data/moc_searchinstance.cpp

compiler_uic_clean:
	@-$(DEL_FILE) ../out/build_data/ui_mainwindow.h ../out/build_data/ui_frmabout.h ../out/build_data/ui_frmpreferences.h ../out/build_data/ui_frmencodingchooser.h ../out/build_data/ui_frmindentationmode.h ../out/build_data/ui_dlgsearching.h ../out/build_data/ui_frmsearchreplace.h ../out/build_data/ui_frmlinenumberchooser.h ../out/build_data/ui_installextension.h

compiler_clean: compiler_rcc_clean compiler_moc_predefs_clean compiler_moc_header_clean compiler_uic_clean

all: $(TARGET)

clean: compiler_clean
	@-$(DEL_FILE) $(OBJ_FILES)
	@-$(DEL_FILE) gschemas.compiled
	@-$(DEL_FILE) ../translations/notepadqq_de.qm ../translations/notepadqq_es.qm ../translations/notepadqq_fr.qm ../translations/notepadqq_hu.qm ../translations/notepadqq_it.qm ../translations/notepadqq_ja.qm ../translations/notepadqq_pl.qm ../translations/notepadqq_pt.qm ../translations/notepadqq_ru.qm ../translations/notepadqq_sl.qm ../translations/notepadqq_sv.qm ../translations/notepadqq_uk.qm ../translations/notepadqq_zh.qm
	@-$(DEL_FILE) *~ core *.core