/*
 *  OpenSCAD (www.openscad.org)
 *  Copyright (C) 2009-2019 Clifford Wolf <clifford@clifford.at> and
 *                          Marius Kintel <marius@kintel.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  As a special exception, you have permission to link this program
 *  with the CGAL library and distribute executables, as long as you
 *  follow the requirements of the GNU GPL in regard to all of the
 *  software in the executable aside from CGAL.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <QString>

#include "PrintService.h"
#include "PrintInitDialog.h"

PrintInitDialog::PrintInitDialog()
{
  setupUi(this);

  const auto printService = PrintService::inst();
  this->textBrowser->setSource(QUrl{"qrc:/src/gui/PrintInitDialog.html"});

  this->okButton->setEnabled(false);

  if (printService->isEnabled()) {
    this->printServiceButton->setText(this->printServiceButton->text().arg(printService->getDisplayName()));
  } else {
    this->printServiceButton->setText(_("Print Service not available"));
    this->printServiceButton->setEnabled(false);
  }
}

PrintInitDialog::~PrintInitDialog()
{
}

void PrintInitDialog::on_printServiceButton_clicked()
{
  this->textBrowser->setHtml(PrintService::inst()->getInfoHtml());
  this->result = print_service_t::PRINT_SERVICE;
  this->okButton->setEnabled(true);
}

void PrintInitDialog::on_octoPrintButton_clicked()
{
  this->textBrowser->setSource(QUrl{"qrc:/src/OctoPrintInfo.html"});
  this->result = print_service_t::OCTOPRINT;
  this->okButton->setEnabled(true);
}

void PrintInitDialog::on_okButton_clicked()
{
  accept();
}

void PrintInitDialog::on_cancelButton_clicked()
{
  reject();
}
