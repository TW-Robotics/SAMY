/* ========================================================================
 * Copyright (c) 2005-2019 The OPC Foundation, Inc. All rights reserved.
 *
 * OPC Foundation MIT License 1.00
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * The complete license agreement can be found here:
 * http://opcfoundation.org/License/MIT/1.00/
 * ======================================================================*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Runtime.Serialization;
using Opc.Ua;

namespace CRCL
{
    #region Uni Class
    #if (!OPCUA_EXCLUDE_Uni)
    /// <summary>
    /// Fraction structure
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    [DataContract(Namespace = CRCL.Namespaces.CRCL)]
    public partial class Uni : Union
    {
        #region Constructors
        /// <summary>
        /// The default constructor.
        /// </summary>
        public Uni()
        {
            Initialize();
        }

        /// <summary>
        /// Called by the .NET framework during deserialization.
        /// </summary>
        [OnDeserializing]
        private void Initialize(StreamingContext context)
        {
            Initialize();
        }

        /// <summary>
        /// Sets private members to default values.
        /// </summary>
        private void Initialize()
        {
            m_switchField = (uint)0;
            m_optionA = (short)0;
            m_optionB = null;
        }
        #endregion

        #region Public Properties
        /// <remarks />
        [DataMember(Name = "switchField", IsRequired = false, Order = 1)]
        public uint switchField
        {
            get { return m_switchField;  }
            set { m_switchField = value; }
        }

        /// <remarks />
        [DataMember(Name = "optionA", IsRequired = false, Order = 2)]
        public short optionA
        {
            get { return m_optionA;  }
            set { m_optionA = value; }
        }

        /// <remarks />
        [DataMember(Name = "optionB", IsRequired = false, Order = 3)]
        public string optionB
        {
            get { return m_optionB;  }
            set { m_optionB = value; }
        }
        #endregion

        #region IEncodeable Members
        /// <summary cref="IEncodeable.TypeId" />
        public override ExpandedNodeId TypeId
        {
            get { return DataTypeIds.Uni; }
        }

        /// <summary cref="IEncodeable.BinaryEncodingId" />
        public override ExpandedNodeId BinaryEncodingId
        {
            get { return ObjectIds.Uni_Encoding_DefaultBinary; }
        }

        /// <summary cref="IEncodeable.XmlEncodingId" />
        public override ExpandedNodeId XmlEncodingId
        {
            get { return ObjectIds.Uni_Encoding_DefaultXml; }
        }

        /// <summary cref="IEncodeable.Encode(IEncoder)" />
        public override void Encode(IEncoder encoder)
        {
            base.Encode(encoder);

            encoder.PushNamespace(CRCL.Namespaces.CRCL);

            encoder.WriteUInt32("switchField", switchField);
            encoder.WriteInt16("optionA", optionA);
            encoder.WriteString("optionB", optionB);

            encoder.PopNamespace();
        }

        /// <summary cref="IEncodeable.Decode(IDecoder)" />
        public override void Decode(IDecoder decoder)
        {
            base.Decode(decoder);

            decoder.PushNamespace(CRCL.Namespaces.CRCL);

            switchField = decoder.ReadUInt32("switchField");
            optionA = decoder.ReadInt16("optionA");
            optionB = decoder.ReadString("optionB");

            decoder.PopNamespace();
        }

        /// <summary cref="IEncodeable.IsEqual(IEncodeable)" />
        public override bool IsEqual(IEncodeable encodeable)
        {
            if (Object.ReferenceEquals(this, encodeable))
            {
                return true;
            }

            Uni value = encodeable as Uni;

            if (value == null)
            {
                return false;
            }

            if (!base.IsEqual(encodeable)) return false;
            if (!Utils.IsEqual(m_switchField, value.m_switchField)) return false;
            if (!Utils.IsEqual(m_optionA, value.m_optionA)) return false;
            if (!Utils.IsEqual(m_optionB, value.m_optionB)) return false;

            return true;
        }    

        #if !NET_STANDARD
        /// <summary cref="ICloneable.Clone" />
        public override object Clone()
        {
            return (Uni)this.MemberwiseClone();
        }
        #endif

        /// <summary cref="Object.MemberwiseClone" />
        public new object MemberwiseClone()
        {
            Uni clone = (Uni)base.MemberwiseClone();

            clone.m_switchField = (uint)Utils.Clone(this.m_switchField);
            clone.m_optionA = (short)Utils.Clone(this.m_optionA);
            clone.m_optionB = (string)Utils.Clone(this.m_optionB);

            return clone;
        }
        #endregion

        #region Private Fields
        private uint m_switchField;
        private short m_optionA;
        private string m_optionB;
        #endregion
    }

    #region UniCollection Class
    /// <summary>
    /// A collection of Uni objects.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    [CollectionDataContract(Name = "ListOfUni", Namespace = CRCL.Namespaces.CRCL, ItemName = "Uni")]
    #if !NET_STANDARD
    public partial class UniCollection : List<Uni>, ICloneable
    #else
    public partial class UniCollection : List<Uni>
    #endif
    {
        #region Constructors
        /// <summary>
        /// Initializes the collection with default values.
        /// </summary>
        public UniCollection() {}

        /// <summary>
        /// Initializes the collection with an initial capacity.
        /// </summary>
        public UniCollection(int capacity) : base(capacity) {}

        /// <summary>
        /// Initializes the collection with another collection.
        /// </summary>
        public UniCollection(IEnumerable<Uni> collection) : base(collection) {}
        #endregion

        #region Static Operators
        /// <summary>
        /// Converts an array to a collection.
        /// </summary>
        public static implicit operator UniCollection(Uni[] values)
        {
            if (values != null)
            {
                return new UniCollection(values);
            }

            return new UniCollection();
        }

        /// <summary>
        /// Converts a collection to an array.
        /// </summary>
        public static explicit operator Uni[](UniCollection values)
        {
            if (values != null)
            {
                return values.ToArray();
            }

            return null;
        }
        #endregion

        #if !NET_STANDARD
        #region ICloneable Methods
        /// <summary>
        /// Creates a deep copy of the collection.
        /// </summary>
        public object Clone()
        {
            return (UniCollection)this.MemberwiseClone();
        }
        #endregion
        #endif

        /// <summary cref="Object.MemberwiseClone" />
        public new object MemberwiseClone()
        {
            UniCollection clone = new UniCollection(this.Count);

            for (int ii = 0; ii < this.Count; ii++)
            {
                clone.Add((Uni)Utils.Clone(this[ii]));
            }

            return clone;
        }
    }
    #endregion
    #endif
    #endregion
}