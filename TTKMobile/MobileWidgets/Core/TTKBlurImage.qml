/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (C) 2015 - 2018 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */
import QtQuick 2.5
import QtGraphicalEffects 1.0

Rectangle{
    id: ttkBlurImage
    clip: true

    property Item target

    FastBlur {
        id: fastBlur
        source: parent.target
        width: source.width
        height: source.height
        radius: 64
    }

    onXChanged: setBlurPosition();
    onYChanged: setBlurPosition();
    Component.onCompleted: setBlurPosition()

    function setBlurPosition() {
        fastBlur.x = target.x - x;
        fastBlur.y = target.y - y;
    }
}
