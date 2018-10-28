EAGLE = eagle
PROJECT = stm32-usb-ble-devkit

SCH = $(PROJECT).sch
BRD = $(PROJECT).brd
CAM = $(PROJECT).cam

GERBERS = copper_bottom.gbr copper_top.gbr \
          silkscreen_bottom.gbr silkscreen_top.gbr \
          soldermask_bottom.gbr soldermask_top.gbr \
          solderpaste_bottom.gbr solderpaste_top.gbr \
          drills.xln \
          gerber_job.gbrjob \
          profile.gbr

.PHONY: clean sch-pdf brd-pdf gerbers

all: sch-pdf brd-pdf gerber.zip

clean:
	$(RM) $(SCH).pdf $(BRD).pdf
	$(RM) $(PROJECT).pdf
	$(RM) $(GERBERS:%=gerber/%) gerber.zip
	$(RM) -r gerber

sch-pdf: $(SCH).pdf
brd-pdf: $(BRD).pdf
%.pdf: %
	$(EAGLE) -C "edit .sch; print file $@ paper A4 sheets ALL landscape; quit;" $^

gerbers: $(GERBERS:%=gerber/%)
gerber:
	mkdir -p $@
$(GERBERS:%=gerber/%): $(BRD) gerber
	$(EAGLE) -X -N -d CAMJOB -j $(CAM) -o . $<
gerber.zip: $(GERBERS:%=gerber/%)
	zip -r $@ $^
