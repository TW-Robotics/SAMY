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
using System.Reflection;
using System.Xml;
using System.Runtime.Serialization;
using Opc.Ua;

namespace CRCL
{
    #region DataType Identifiers
    /// <summary>
    /// A class that declares constants for all DataTypes in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class DataTypes
    {
        /// <summary>
        /// The identifier for the Uni DataType.
        /// </summary>
        public const uint Uni = 15001;
    }
    #endregion

    #region Object Identifiers
    /// <summary>
    /// A class that declares constants for all Objects in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class Objects
    {
        /// <summary>
        /// The identifier for the Uni_Encoding_DefaultBinary Object.
        /// </summary>
        public const uint Uni_Encoding_DefaultBinary = 15002;

        /// <summary>
        /// The identifier for the Uni_Encoding_DefaultXml Object.
        /// </summary>
        public const uint Uni_Encoding_DefaultXml = 15010;

        /// <summary>
        /// The identifier for the Uni_Encoding_DefaultJson Object.
        /// </summary>
        public const uint Uni_Encoding_DefaultJson = 15018;
    }
    #endregion

    #region Variable Identifiers
    /// <summary>
    /// A class that declares constants for all Variables in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class Variables
    {
        /// <summary>
        /// The identifier for the CRCL_BinarySchema Variable.
        /// </summary>
        public const uint CRCL_BinarySchema = 15003;

        /// <summary>
        /// The identifier for the CRCL_BinarySchema_NamespaceUri Variable.
        /// </summary>
        public const uint CRCL_BinarySchema_NamespaceUri = 15005;

        /// <summary>
        /// The identifier for the CRCL_BinarySchema_Deprecated Variable.
        /// </summary>
        public const uint CRCL_BinarySchema_Deprecated = 15006;

        /// <summary>
        /// The identifier for the CRCL_BinarySchema_Uni Variable.
        /// </summary>
        public const uint CRCL_BinarySchema_Uni = 15007;

        /// <summary>
        /// The identifier for the CRCL_XmlSchema Variable.
        /// </summary>
        public const uint CRCL_XmlSchema = 15011;

        /// <summary>
        /// The identifier for the CRCL_XmlSchema_NamespaceUri Variable.
        /// </summary>
        public const uint CRCL_XmlSchema_NamespaceUri = 15013;

        /// <summary>
        /// The identifier for the CRCL_XmlSchema_Deprecated Variable.
        /// </summary>
        public const uint CRCL_XmlSchema_Deprecated = 15014;

        /// <summary>
        /// The identifier for the CRCL_XmlSchema_Uni Variable.
        /// </summary>
        public const uint CRCL_XmlSchema_Uni = 15015;
    }
    #endregion

    #region DataType Node Identifiers
    /// <summary>
    /// A class that declares constants for all DataTypes in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class DataTypeIds
    {
        /// <summary>
        /// The identifier for the Uni DataType.
        /// </summary>
        public static readonly ExpandedNodeId Uni = new ExpandedNodeId(CRCL.DataTypes.Uni, CRCL.Namespaces.CRCL);
    }
    #endregion

    #region Object Node Identifiers
    /// <summary>
    /// A class that declares constants for all Objects in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class ObjectIds
    {
        /// <summary>
        /// The identifier for the Uni_Encoding_DefaultBinary Object.
        /// </summary>
        public static readonly ExpandedNodeId Uni_Encoding_DefaultBinary = new ExpandedNodeId(CRCL.Objects.Uni_Encoding_DefaultBinary, CRCL.Namespaces.CRCL);

        /// <summary>
        /// The identifier for the Uni_Encoding_DefaultXml Object.
        /// </summary>
        public static readonly ExpandedNodeId Uni_Encoding_DefaultXml = new ExpandedNodeId(CRCL.Objects.Uni_Encoding_DefaultXml, CRCL.Namespaces.CRCL);

        /// <summary>
        /// The identifier for the Uni_Encoding_DefaultJson Object.
        /// </summary>
        public static readonly ExpandedNodeId Uni_Encoding_DefaultJson = new ExpandedNodeId(CRCL.Objects.Uni_Encoding_DefaultJson, CRCL.Namespaces.CRCL);
    }
    #endregion

    #region Variable Node Identifiers
    /// <summary>
    /// A class that declares constants for all Variables in the Model Design.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class VariableIds
    {
        /// <summary>
        /// The identifier for the CRCL_BinarySchema Variable.
        /// </summary>
        public static readonly ExpandedNodeId CRCL_BinarySchema = new ExpandedNodeId(CRCL.Variables.CRCL_BinarySchema, CRCL.Namespaces.CRCL);

        /// <summary>
        /// The identifier for the CRCL_BinarySchema_NamespaceUri Variable.
        /// </summary>
        public static readonly ExpandedNodeId CRCL_BinarySchema_NamespaceUri = new ExpandedNodeId(CRCL.Variables.CRCL_BinarySchema_NamespaceUri, CRCL.Namespaces.CRCL);

        /// <summary>
        /// The identifier for the CRCL_BinarySchema_Deprecated Variable.
        /// </summary>
        public static readonly ExpandedNodeId CRCL_BinarySchema_Deprecated = new ExpandedNodeId(CRCL.Variables.CRCL_BinarySchema_Deprecated, CRCL.Namespaces.CRCL);

        /// <summary>
        /// The identifier for the CRCL_BinarySchema_Uni Variable.
        /// </summary>
        public static readonly ExpandedNodeId CRCL_BinarySchema_Uni = new ExpandedNodeId(CRCL.Variables.CRCL_BinarySchema_Uni, CRCL.Namespaces.CRCL);

        /// <summary>
        /// The identifier for the CRCL_XmlSchema Variable.
        /// </summary>
        public static readonly ExpandedNodeId CRCL_XmlSchema = new ExpandedNodeId(CRCL.Variables.CRCL_XmlSchema, CRCL.Namespaces.CRCL);

        /// <summary>
        /// The identifier for the CRCL_XmlSchema_NamespaceUri Variable.
        /// </summary>
        public static readonly ExpandedNodeId CRCL_XmlSchema_NamespaceUri = new ExpandedNodeId(CRCL.Variables.CRCL_XmlSchema_NamespaceUri, CRCL.Namespaces.CRCL);

        /// <summary>
        /// The identifier for the CRCL_XmlSchema_Deprecated Variable.
        /// </summary>
        public static readonly ExpandedNodeId CRCL_XmlSchema_Deprecated = new ExpandedNodeId(CRCL.Variables.CRCL_XmlSchema_Deprecated, CRCL.Namespaces.CRCL);

        /// <summary>
        /// The identifier for the CRCL_XmlSchema_Uni Variable.
        /// </summary>
        public static readonly ExpandedNodeId CRCL_XmlSchema_Uni = new ExpandedNodeId(CRCL.Variables.CRCL_XmlSchema_Uni, CRCL.Namespaces.CRCL);
    }
    #endregion

    #region BrowseName Declarations
    /// <summary>
    /// Declares all of the BrowseNames used in the Model Design.
    /// </summary>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class BrowseNames
    {
        /// <summary>
        /// The BrowseName for the CRCL_BinarySchema component.
        /// </summary>
        public const string CRCL_BinarySchema = "CRCL";

        /// <summary>
        /// The BrowseName for the CRCL_XmlSchema component.
        /// </summary>
        public const string CRCL_XmlSchema = "CRCL";

        /// <summary>
        /// The BrowseName for the Uni component.
        /// </summary>
        public const string Uni = "Uni";
    }
    #endregion

    #region Namespace Declarations
    /// <summary>
    /// Defines constants for all namespaces referenced by the model design.
    /// </summary>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public static partial class Namespaces
    {
        /// <summary>
        /// The URI for the CRCL namespace (.NET code namespace is 'CRCL').
        /// </summary>
        public const string CRCL = "https://crcl.org";

        /// <summary>
        /// The URI for the OpcUa namespace (.NET code namespace is 'Opc.Ua').
        /// </summary>
        public const string OpcUa = "http://opcfoundation.org/UA/";

        /// <summary>
        /// The URI for the OpcUaXsd namespace (.NET code namespace is 'Opc.Ua').
        /// </summary>
        public const string OpcUaXsd = "http://opcfoundation.org/UA/2008/02/Types.xsd";
    }
    #endregion
}