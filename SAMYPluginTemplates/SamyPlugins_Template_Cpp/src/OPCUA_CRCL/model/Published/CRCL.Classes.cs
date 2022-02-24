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
    #region ISkillParameterState Class
    #if (!OPCUA_EXCLUDE_ISkillParameterState)
    /// <summary>
    /// Stores an instance of the ISkillParameter ObjectType.
    /// </summary>
    /// <exclude />
    [System.CodeDom.Compiler.GeneratedCodeAttribute("Opc.Ua.ModelCompiler", "1.0.0.0")]
    public partial class ISkillParameterState : BaseInterfaceState
    {
        #region Constructors
        /// <summary>
        /// Initializes the type with its default attribute values.
        /// </summary>
        public ISkillParameterState(NodeState parent) : base(parent)
        {
        }

        /// <summary>
        /// Returns the id of the default type definition node for the instance.
        /// </summary>
        protected override NodeId GetDefaultTypeDefinitionId(NamespaceTable namespaceUris)
        {
            return Opc.Ua.NodeId.Create(CRCL.ObjectTypes.ISkillParameter, CRCL.Namespaces.CRCL, namespaceUris);
        }

        #if (!OPCUA_EXCLUDE_InitializationStrings)
        /// <summary>
        /// Initializes the instance.
        /// </summary>
        protected override void Initialize(ISystemContext context)
        {
            Initialize(context, InitializationString);
            InitializeOptionalChildren(context);
        }

        /// <summary>
        /// Initializes the instance with a node.
        /// </summary>
        protected override void Initialize(ISystemContext context, NodeState source)
        {
            InitializeOptionalChildren(context);
            base.Initialize(context, source);
        }

        /// <summary>
        /// Initializes the any option children defined for the instance.
        /// </summary>
        protected override void InitializeOptionalChildren(ISystemContext context)
        {
            base.InitializeOptionalChildren(context);
        }

        #region Initialization String
        private const string InitializationString =
           "AQAAABAAAABodHRwczovL2NyY2wub3Jn/////4RggAIBAAAAAQAXAAAASVNraWxsUGFyYW1ldGVySW5z" +
           "dGFuY2UBAQE7AQEBOwE7AAAB/////wEAAAA1YIkKAgAAAAEAHAAAAFJlYWRQYXJhbWV0ZXJBdEV4ZWN1" +
           "dGlvblRpbWUBAQI7AwAAAADiAAAAV2hlbiBpbnN0YW50aWF0aW5nIGEgc2tpbGwgKGNhbGxpbmcgdGhl" +
           "IFN0YXJ0IG1ldGhvZCksIHdpdGggdGhpcyB2YXJpYWJsZSBvbmUgY2FuIGluZGljYXRlIHdoZXRoZXIg" +
           "YSBjb21tYW5kIHVzZXMgYSBmaXhlZCBwYXJhbWV0ZXIsIHNldCBhdCBza2lsbCBpbnN0YW50YXRpb24g" +
           "dGltZSwgb3IgYSAicmVhbCB0aW1lIiB2YWx1ZSByZWFkIGF0IGV4ZWN1dGlvbiB0aW1lIG9mIHRoZSBj" +
           "b21tYW5kLgAuAEQCOwAAAAH/////AQH/////AAAAAA==";
        #endregion
        #endif
        #endregion

        #region Public Properties
        /// <remarks />
        public PropertyState<bool> ReadParameterAtExecutionTime
        {
            get
            {
                return m_readParameterAtExecutionTime;
            }

            set
            {
                if (!Object.ReferenceEquals(m_readParameterAtExecutionTime, value))
                {
                    ChangeMasks |= NodeStateChangeMasks.Children;
                }

                m_readParameterAtExecutionTime = value;
            }
        }
        #endregion

        #region Overridden Methods
        /// <summary>
        /// Populates a list with the children that belong to the node.
        /// </summary>
        /// <param name="context">The context for the system being accessed.</param>
        /// <param name="children">The list of children to populate.</param>
        public override void GetChildren(
            ISystemContext context,
            IList<BaseInstanceState> children)
        {
            if (m_readParameterAtExecutionTime != null)
            {
                children.Add(m_readParameterAtExecutionTime);
            }

            base.GetChildren(context, children);
        }

        /// <summary>
        /// Finds the child with the specified browse name.
        /// </summary>
        protected override BaseInstanceState FindChild(
            ISystemContext context,
            QualifiedName browseName,
            bool createOrReplace,
            BaseInstanceState replacement)
        {
            if (QualifiedName.IsNull(browseName))
            {
                return null;
            }

            BaseInstanceState instance = null;

            switch (browseName.Name)
            {
                case CRCL.BrowseNames.ReadParameterAtExecutionTime:
                {
                    if (createOrReplace)
                    {
                        if (ReadParameterAtExecutionTime == null)
                        {
                            if (replacement == null)
                            {
                                ReadParameterAtExecutionTime = new PropertyState<bool>(this);
                            }
                            else
                            {
                                ReadParameterAtExecutionTime = (PropertyState<bool>)replacement;
                            }
                        }
                    }

                    instance = ReadParameterAtExecutionTime;
                    break;
                }
            }

            if (instance != null)
            {
                return instance;
            }

            return base.FindChild(context, browseName, createOrReplace, replacement);
        }
        #endregion

        #region Private Fields
        private PropertyState<bool> m_readParameterAtExecutionTime;
        #endregion
    }
    #endif
    #endregion
}