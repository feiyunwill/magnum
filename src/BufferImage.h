#ifndef Magnum_BufferImage_h
#define Magnum_BufferImage_h
/*
    Copyright © 2010, 2011, 2012 Vladimír Vondruš <mosra@centrum.cz>

    This file is part of Magnum.

    Magnum is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License version 3
    only, as published by the Free Software Foundation.

    Magnum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License version 3 for more details.
*/

#ifndef MAGNUM_TARGET_GLES2
/** @file
 * @brief Class Magnum::BufferImage, typedef Magnum::BufferImage1D, Magnum::BufferImage2D, Magnum::BufferImage3D
 */
#endif

#include "Math/Vector3.h"
#include "AbstractImage.h"
#include "Buffer.h"
#include "DimensionTraits.h"

namespace Magnum {

#ifndef MAGNUM_TARGET_GLES2
/**
@brief %Buffer image

Stores image data in GPU memory. Interchangeable with Image, ImageWrapper or
Trade::ImageData.
@see BufferImage1D, BufferImage2D, BufferImage3D, Buffer
@requires_gles30 Pixel buffer objects are not available in OpenGL ES 2.0.
*/
template<UnsignedInt dimensions> class MAGNUM_EXPORT BufferImage: public AbstractImage {
    public:
        const static UnsignedInt Dimensions = dimensions; /**< @brief %Image dimension count */

        /**
         * @brief Constructor
         * @param format            Format of pixel data
         * @param type              Data type of pixel data
         *
         * Dimensions and buffer are empty, call setData() to fill the image
         * with data.
         */
        inline explicit BufferImage(Format format, Type type): AbstractImage(format, type) {
            _buffer.setTargetHint(Buffer::Target::PixelPack);
        }

        /** @brief %Image size */
        inline typename DimensionTraits<Dimensions, Int>::VectorType size() const { return _size; }

        /** @brief %Image buffer */
        inline Buffer* buffer() { return &_buffer; }

        /**
         * @brief Set image data
         * @param size              %Image size
         * @param format            Format of pixel data
         * @param type              Data type of pixel data
         * @param data              %Image data
         * @param usage             %Image buffer usage
         *
         * Updates the image buffer with given data. The data are not deleted
         * after filling the buffer.
         *
         * @see Buffer::setData()
         */
        void setData(const typename DimensionTraits<Dimensions, Int>::VectorType& size, Format format, Type type, const GLvoid* data, Buffer::Usage usage);

    private:
        Math::Vector<Dimensions, Int> _size;
        Buffer _buffer;
};

/** @brief One-dimensional buffer image */
typedef BufferImage<1> BufferImage1D;

/** @brief Two-dimensional buffer image */
typedef BufferImage<2> BufferImage2D;

/** @brief Three-dimensional buffer image */
typedef BufferImage<3> BufferImage3D;
#endif

}

#endif
